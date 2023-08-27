#pragma once

#include <Windows.h>

#include <filesystem>
#include <string>

#include "fileutil.hpp"

namespace fileutil
{
	struct platform_specific_file_handler
	{
	public:
		using file_handle_t = HANDLE;

		file_handle_t file_handle;

		platform_specific_file_handler() = delete;
		explicit platform_specific_file_handler(std::filesystem::path const& fp)
		{
			auto const path_str = fp.string(); // Need tmp var for lifetime rules (lvalue).
			file_handle = CreateFileA(
				path_str.c_str(),
				GENERIC_WRITE,
				0,
				NULL,
				OPEN_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL
			);
		}

		~platform_specific_file_handler()
		{
			CloseHandle(this->file_handle);
		}
	};
}