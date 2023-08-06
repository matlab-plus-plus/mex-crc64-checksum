/*
* Test utilities for dealing with files.
*/

#pragma once

#include <filesystem>

namespace fileutil
{
	// File-scope constants
	inline std::filesystem::path const windows_long_path_prefix{ R"(\\?\)" };

	// Function for creating file if it doesn't already exist.
	[[maybe_unused]] bool create_file(std::filesystem::path const& file_name, std::string_view contents = "");
}