#include "longpath.hpp"

#include <filesystem>
#include <stdint.h>
#include <string>
#include <string_view>
#include <system_error>

inline namespace
{
	/*
	* Checks if a path starts with the Windows long path prefix.
	* 
	* Handles wide character formats in case they're being used.
	*/
	bool starts_with_long_path_prefix(std::filesystem::path const& fp)
	{
		try
		{
			return fp.generic_string().starts_with(fileutil::windows_long_path_prefix);
		}
		catch (std::system_error const& se)
		{
			// Attempt to remedy our error condition by performing a widening conversion.
			return fp.generic_wstring().starts_with(fileutil::windows_long_path_prefix_wide);
		}
	}

	/*
	* Creates a new path object with the Windows long path prefix prepended.
	* 
	* Handles wide character formats in case they're required.
	* 
	* Canonicalization is necessary before adding the prefix because
	* Windows will not do any path expansion after the prefix is added.
	*/
	std::filesystem::path add_long_path_prefix(std::filesystem::path const& fp)
	{
		try
		{
			return std::filesystem::path(
				std::string(fileutil::windows_long_path_prefix) + std::filesystem::weakly_canonical(fp).string()
			);
		}
		catch (std::system_error const& se)
		{
			return std::filesystem::path(
				std::wstring(fileutil::windows_long_path_prefix_wide) + std::filesystem::weakly_canonical(fp).wstring()
			);
		}
	}
}

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
		if (starts_with_long_path_prefix(file_path))
			return file_path;

		return add_long_path_prefix(file_path);
	}

	std::size_t path_length(std::filesystem::path const& file_path) noexcept
	{
		return file_path.wstring().length();
	}
}