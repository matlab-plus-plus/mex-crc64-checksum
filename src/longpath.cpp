#include "longpath.hpp"

#include <filesystem>
#include <string>

namespace fileutil
{
	std::filesystem::path create_long_path(std::filesystem::path const& file_path)
	{
		// Simply return the input if *not* Windows, since other operating
		// systems don't impose the same restriction as Windows.
		#ifndef _WIN32
			return file_path;
		#endif

		// Return the input if it already begins with the Windows
		// long path prefix.
		if (file_path.string().starts_with(windows_long_path_prefix))
			return file_path;

		return std::filesystem::path(
			windows_long_path_prefix + file_path.string()
		);
	}
}