/*
* Source for computing the checksum of a directory.
*/

#include "crc.hpp"
#include "private/directory_checksum_mt.hpp"
#include "private/chk_fmt.hpp"
#include "private/ext_def.hpp"

#include <algorithm>
#include <cassert>
#include <execution>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace
{
	struct file_code
	{
		fs::path path{};
		crc::checksum_t checksum{};

		file_code(void) = default;

		file_code(fs::path const p, crc::checksum_t const chksm) :
			path(p), checksum(chksm) {}
	};

	crc::checksum_t codeListToChecksum(std::vector<file_code> const& codeList)
	{
		crc::ext::boost_crc64 calc{};
		calc.reset();

		std::vector<crc::checksum_t> chksmList(codeList.size());
		std::transform(codeList.cbegin(), codeList.cend(), chksmList.begin(),
			[](auto const v) {return v.checksum; });

		calc.process_bytes(chksmList.data(), chksmList.size());

		return calc.checksum();
	}
}

namespace crc
{
	std::string str_dir_checksum(fs::path const dir)
	{
		return _internal::format_checksum(calc_dir_checksum(dir));
	}

	checksum_t calc_dir_checksum(fs::path const dir)
	{
		assert(fs::is_directory(dir) /* Provided path must be a directory. */);
		
		// Extract all directory_entry paths from the directory, recursively.
		auto pathVect = std::vector<fs::path>();
		pathVect.reserve(1000u);

		for (fs::directory_entry const& dir_entry :
			fs::recursive_directory_iterator(dir))
		{
			if (dir_entry.is_regular_file())
				pathVect.push_back(dir_entry.path());
		}

		// Compute the checksum of all the files in the directory
		// and then sort them
		std::vector<file_code> codeList{ pathVect.size() };
		std::transform(std::execution::par,
			pathVect.cbegin(), pathVect.cend(), codeList.begin(),
			[](auto const& p) {return file_code(p, calc_checksum(p)); });

		// Sort the codes
		std::sort(codeList.begin(), codeList.end(),
			[](file_code const& L, file_code const& R) {return L.path < R.path; });

		// Combine the codes together to form a single checksum
		return codeListToChecksum(codeList);
	}
}