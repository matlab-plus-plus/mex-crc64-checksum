/*
* Utilities for dealing with long filepaths.
*/

#pragma once

#include <filesystem>
#include <stdint.h>
#include <string>

namespace fileutil
{
	// File-scope constants
	inline std::string const windows_long_path_prefix{ R"(\\?\)" };
	inline constexpr std::size_t windows_max_path_length{ 260u };

	// Adds the Windows long path prefix if the system is Windows.
	// Returns a normal std::filesystem::path object.
	std::filesystem::path create_long_path(std::filesystem::path const& file_path);

	// Returns the length of a path
	std::size_t path_length(std::filesystem::path const& file_path) noexcept;
}