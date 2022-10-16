#include "crc.hpp"
#include "private/directory_checksum_mt.hpp"

#include "mex.hpp"
#include "mexAdapter.hpp"
#include "MatlabDataArray.hpp"

#include <filesystem>
#include <sstream>

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
				ss << textInput.toAscii();
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