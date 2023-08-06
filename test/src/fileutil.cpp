
#include "fileutil.hpp"

#include <filesystem>
#include <fstream>
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
}