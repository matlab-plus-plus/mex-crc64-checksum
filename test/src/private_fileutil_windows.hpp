#pragma once

#include <Windows.h>

#include <filesystem>

namespace fileutil
{
	struct platform_specific_file_handler
	{
	public:
		using file_handle_t = HANDLE;

		file_handle_t file_handle;

		platform_specific_file_handler() = delete;
		explicit platform_specific_file_handler(std::filesystem::path const& fp) :
			file_handle(
				CreateFileA(
					fp.string().c_str(),
					GENERIC_WRITE,
					0,
					NULL,
					OPEN_ALWAYS,
					FILE_ATTRIBUTE_NORMAL,
					NULL
				)
			) {}

		~platform_specific_file_handler()
		{
			CloseHandle(this->file_handle);
		}
	};
}