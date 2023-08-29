#include "crc.hpp"
#include "private/chk_fmt.hpp"
#include "private/ext_def.hpp"

#include "longpath.hpp"

#include <filesystem>
#include <fstream>
#include <istream>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>

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
		auto ifs = std::ifstream(fileutil::create_long_path(fp), fset); // TODO: Investigate the performance implications of an unconditional longpath conversion.

		if (ifs.fail())
			throw file_open_error("Failed to open file '" + fp.string() + "' while attempting to calculate checksum.");

		return calc_checksum(ifs);
	}

	checksum_t calc_checksum(std::istream& is)
	{
		/* Calculates the checksum of an input stream */
		if (is.fail())
			throw invalid_stream_error("Input stream invalid i.e. fail() method is true.");

		ext::boost_crc64 crc64_calc{};
		crc64_calc.reset();

		unsigned char thisByte;
		do {
			thisByte = static_cast<unsigned char>(is.get());

			if (!is.good())
			{
				// Get operation above returned garbage because end-of-file
				// was reached or there was a problem.
				break;
			}

			crc64_calc.process_byte(thisByte);
		} while (true);

		return crc64_calc.checksum();
	}

	checksum_t calc_checksum(std::string_view sv) noexcept
	{
		/* Calculates the checksum of a string */
		ext::boost_crc64 crc64_calc{};
		crc64_calc.reset();

		std::ranges::for_each(
			sv,
			[&crc64_calc](unsigned char this_byte) {crc64_calc.process_byte(this_byte); }
		);

		return crc64_calc.checksum();
	}

	// Exceptions
	invalid_stream_error::invalid_stream_error(std::string const& what_str) : std::runtime_error(what_str) {}
	file_open_error::file_open_error(std::string const& what_str) : std::runtime_error(what_str) {}
}