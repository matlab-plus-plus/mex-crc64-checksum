/*
* Test utilities for dealing with files.
*/

#pragma once

#include "longpath.hpp"

#include <filesystem>
#include <memory>
#include <string>

namespace fileutil
{
	// Function for creating file if it doesn't already exist.
	[[maybe_unused]] bool create_file(std::filesystem::path const& file_name, std::string_view contents = "");

	// Function for creating long file
	void create_long_file(std::filesystem::path const& file_name, std::string_view contents = "");

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

	// Class for attempting to delete a file when the object goes out of scope.
	// If this class fails to delete the file, nothing happens.
	class scoped_file_deleter
	{
		std::filesystem::path fp;
	public:
		scoped_file_deleter() = delete;
		explicit scoped_file_deleter(std::filesystem::path const& fp) : fp(fp) {}
		~scoped_file_deleter();
	};
}