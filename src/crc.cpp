#include "crc.hpp"
#include "private/chk_fmt.hpp"
#include "private/ext_def.hpp"

#include <filesystem>
#include <fstream>
#include <istream>
#include <string>

namespace crc
{
	//checksum_t should be same as boost::ulong_long_type
	//   TODO: Add static_assert to check this

	std::string str_checksum(std::filesystem::path const fp)
	{
		return _internal::format_checksum(calc_checksum(fp));
	}
	std::string str_checksum(std::istream& is)
	{
		return _internal::format_checksum(calc_checksum(is));
	}

	checksum_t calc_checksum(std::filesystem::path const fp)
	{
		/* Calculates the checksum of a file. */

		// File opening setting
		static constexpr auto fset =
			std::ifstream::binary | // Read bytes EXACTLY as they appear in file
			std::ifstream::in;      // Open with read-only permissions
		auto ifs = std::ifstream(fp, fset);
		return calc_checksum(ifs);
	}

	checksum_t calc_checksum(std::istream& is)
	{
		/* Calculates the checksum of an input stream */
		ext::boost_crc64 crc64_calc{};
		crc64_calc.reset();

		unsigned char thisByte;
		do {
			thisByte = static_cast<unsigned char>(is.get());

			if (is.eof())
			{
				// Get operation above returned garbage because end-of-file was reached
				break;
			}

			crc64_calc.process_byte(thisByte);
		} while (true);

		return crc64_calc.checksum();
	}
}