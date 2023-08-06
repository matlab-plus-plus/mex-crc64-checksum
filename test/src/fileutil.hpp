/*
* Test utilities for dealing with files.
*/

#pragma once

#include <filesystem>
#include <memory>

namespace fileutil
{
	// File-scope constants
	inline std::filesystem::path const windows_long_path_prefix{ R"(\\?\)" };

	// Function for creating file if it doesn't already exist.
	[[maybe_unused]] bool create_file(std::filesystem::path const& file_name, std::string_view contents = "");

	// Class for holding a file open in a safe way
	struct platform_specific_file_handler;
	class file_hold_token
	{
	private:
		std::unique_ptr<platform_specific_file_handler> file_handler;
		file_hold_token() = delete;
		explicit file_hold_token(std::filesystem::path const& fp);
	public:
		// Factory method to create a new ``file_hold_token`` object.
		[[nodiscard]] static file_hold_token create(std::filesystem::path const& file_name);
		~file_hold_token();
	};
}