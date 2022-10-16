#include "crc.hpp"
#include "application/codes.hpp"
#include "private/directory_checksum_mt.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <format>

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		std::cerr << "Provide file path\n";
		return codes::return_code<codes::eReturnCode::ARGUMENT_ERROR>;
	}

	std::filesystem::path f{ argv[1] };

	if (!std::filesystem::exists(f))
	{
		std::cerr << "File '" << f << "' does not exist\n";
		return codes::return_code<codes::eReturnCode::FILE_NOT_FOUND_ERROR>;
	}

	if (std::filesystem::is_directory(f))
	{
		std::cout << crc::str_dir_checksum(f);
		return codes::return_code<codes::eReturnCode::SUCCESS>;
	}

	/* Open input filestream from provided file */
	std::cout << crc::str_checksum(f) << std::endl;

	return codes::return_code<codes::eReturnCode::SUCCESS>;
}