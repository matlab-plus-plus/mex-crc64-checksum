/*
* Utilities for dealing with long filepaths.
*/

#pragma once

#include <filesystem>
#include <string>

namespace fileutil
{
	// File-scope constants
	inline std::string const windows_long_path_prefix{ R"(\\?\)" };

	// Adds the Windows long path prefix if the system is Windows.
	// Returns a normal std::filesystem::path object.
	std::filesystem::path create_long_path(std::filesystem::path const& file_path);
}