#include "crc.hpp"
#include "private/directory_checksum_mt.hpp"

#include "mex.hpp"
#include "mexAdapter.hpp"
#include "MatlabDataArray.hpp"

#include <filesystem>
#include <sstream>


namespace
{
	// Forward declarations
	bool manual_ascii_get(matlab::data::CharArray const&, std::stringstream&);
	void str16_to_stringstream(matlab::data::String const&, std::stringstream&);
}

class MexFunction : public matlab::mex::Function {
public:
	void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) override
	{
		unsigned int opt = inputs[0][0];
		matlab::data::CharArray textInput = inputs[1];

		crc::checksum_t outVal{ 0U };
		switch (opt)
		{
			case 0U :
			{
				// Compute checksum of a file
				std::filesystem::path fp{ textInput.toAscii() };
				outVal = crc::calc_checksum(fp);
				break;
			}
			case 1U :
			{
				// Compute checksum of a string
				std::stringstream ss;
				try {
					// First try to interpret the input as just ASCII
					ss << textInput.toAscii();
				}
				catch (matlab::data::NonAsciiCharInRequestedAsciiOutputException const&)
				{
					// Interpret the input as UTF-16 if toAscii() and manual conversion fails
					if (!manual_ascii_get(textInput, ss))
						str16_to_stringstream(textInput.toUTF16(), ss);
				}
				outVal = crc::calc_checksum(ss);
				break;
			}
			case 2U :
			{
				// Compute checksum of a folder
				std::filesystem::path fp{ textInput.toAscii() };
				outVal = crc::calc_dir_checksum(fp);
				break;
			}
			default :
				break;
		}

		matlab::data::ArrayFactory factory;
		outputs[0] = factory.createScalar<crc::checksum_t>(outVal);
	}
};

namespace
{
	bool manual_ascii_get(matlab::data::CharArray const& str, std::stringstream& ss)
	{
		/*
		* Attempt to manually convert a CharArray to a stringstream in case the
		* builtin Matlab method fails. This function returns false if it also fails.
		*/
		for (auto const v : str)
		{
			std::uint16_t const v_as_int{ v };

			// First check high-order bytes to ensure they're zero. If not,
			// we must return false because it would be a narrowing conversion
			// causing loss of data.
			constexpr std::uint16_t high_mask{ 0b1111'1111'0000'0000 };
			constexpr std::uint16_t low_mask{ static_cast<std::uint16_t>(~high_mask) };
			constexpr std::uint16_t zero{ 0b0000'0000'0000'0000 };
			if ((v_as_int & high_mask) != zero)
			{
				// Reset stringstream input because we may have modified it.
				ss.str("");
				ss.clear();

				return false;
			}
			
			ss << static_cast<char>(v_as_int & low_mask);
		}

		return true;
	}

	void str16_to_stringstream(matlab::data::String const& str16, std::stringstream& ss)
	{
		/*   Adapted from https://stackoverflow.com/a/73124234   */
		for (char16_t const c : str16)
		{
			ss << static_cast<char>(c >> 8);
			ss << static_cast<char>(c);
		}
	}
}