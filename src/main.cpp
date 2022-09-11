#include "crc.hpp"
#include "application/codes.hpp"

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

	/* Open input filestream from provided file */
	std::cout << crc::str_checksum(f) << std::endl;

	return codes::return_code<codes::eReturnCode::SUCCESS>;
}