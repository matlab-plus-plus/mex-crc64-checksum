
#include "fileutil.hpp"

#include "private_fileutil_windows.hpp"

#include <filesystem>
#include <fstream>
#include <memory>
#include <stdio.h>
#include <string_view>

namespace fileutil
{
	std::filesystem::path create_long_path(std::filesystem::path const& file_path)
	{
		// Simply return the input if *not* Windows, since other operating
		// systems don't impose the same restriction as Windows.
#		ifndef _WIN32
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

	[[maybe_unused]] bool create_file(std::filesystem::path const& file_name, std::string_view contents)
	{
		if (std::filesystem::exists(file_name))
			return false;

		auto fs = std::ofstream(file_name, std::ios::out);
		if (!contents.empty())
			fs << contents;

		return true;
	}

	void create_long_file(std::filesystem::path const& fp)
	{
		auto scoped_file_creator = platform_specific_file_handler(
			create_long_path(fp)
		);
	}

	file_hold_token::file_hold_token(std::filesystem::path const& fp)
	{
		this->file_handler = std::make_unique<platform_specific_file_handler>(fp);
	}

	file_hold_token::~file_hold_token() = default;

	[[nodiscard]] file_hold_token file_hold_token::create(std::filesystem::path const& fp)
	{
		return file_hold_token(fp);
	}

	scoped_file_deleter::~scoped_file_deleter()
	{
		try
		{
			std::filesystem::remove(this->fp);
		}
		catch (...) {/* Can't throw in a destructor.*/} 
	}
}