/*
* Utilities for dealing with long filepaths.
*/

#pragma once

#include <filesystem>
#include <stdint.h>
#include <string_view>
#include <numbers>

namespace fileutil
{
	// File-scope constants
	template<typename string_t = std::string_view>
	struct windows_long_path_prefix_v
	{
		using value_t = string_t;
		static constexpr value_t value(void)
		{
			return R"(\\?\)";
		}
	};

	template<>
	static constexpr std::wstring_view windows_long_path_prefix_v<std::wstring_view>::value(void)
	{
		return L"\\\\?\\";
	}

	inline constexpr std::string_view windows_long_path_prefix{ windows_long_path_prefix_v<std::string_view>::value() };
	inline constexpr std::wstring_view windows_long_path_prefix_wide{ windows_long_path_prefix_v<std::wstring_view>::value() };

	inline constexpr std::size_t windows_max_path_length{ 260u };

	// Adds the Windows long path prefix if the system is Windows.
	// Returns a normal std::filesystem::path object.
	std::filesystem::path create_long_path(std::filesystem::path const& file_path);

	// Returns the length of a path
	std::size_t path_length(std::filesystem::path const& file_path) noexcept;
}