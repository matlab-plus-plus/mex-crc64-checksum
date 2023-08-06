
#include "fileutil.hpp"

#include "private_fileutil_windows.hpp"

#include <filesystem>
#include <fstream>
#include <memory>
#include <stdio.h>
#include <string_view>

namespace fileutil
{
	[[maybe_unused]] bool create_file(std::filesystem::path const& file_name, std::string_view contents)
	{
		if (std::filesystem::exists(file_name))
			return false;

		auto fs = std::ofstream(file_name, std::ios::out);
		if (!contents.empty())
			fs << contents;

		return true;
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
}