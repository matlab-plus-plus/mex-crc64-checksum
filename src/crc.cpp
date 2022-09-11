#include "crc.hpp"

#include "boost/crc.hpp"

#include <filesystem>
#include <format>
#include <fstream>
#include <istream>
#include <string>

namespace {
	// CRC-64/XZ from https://reveng.sourceforge.io/crc-catalogue/all.htm
	using boost_crc64 = boost::crc_optimal< 64, 0x42f0e1eba9ea3693, 0xffffffffffffffff, 0xffffffffffffffff, true, true >;

	// Persistent crc64 calculator
	boost_crc64 crc64_calc;

	std::string format_checksum(crc::checksum_t const csum)
	{
		return std::format("{:016X}", csum);
	}
}

namespace crc
{
	//checksum_t should be same as boost::ulong_long_type
	//   TODO: Add static_assert to check this

	std::string str_checksum(std::filesystem::path const fp)
	{
		return format_checksum(calc_checksum(fp));
	}
	std::string str_checksum(std::istream& is)
	{
		return format_checksum(calc_checksum(is));
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