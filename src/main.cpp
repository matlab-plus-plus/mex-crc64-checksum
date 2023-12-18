#include "crc.hpp"
#include "application/codes.hpp"
#include "private/directory_checksum_mt.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <format>

int handle_checksum_calculation(std::filesystem::path const& fp);

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

	try
	{
		return handle_checksum_calculation(f);
	}
	catch (crc::file_open_error const& foe)
	{
		std::cout << "Failed calculating checksum:\n\t" << foe.what();
		return codes::return_code<codes::eReturnCode::FILE_OPEN_ERROR>;
	}
	catch (...)
	{
		std::cout << "Failed calculating checksum for unknown reason.";
		return codes::return_code<codes::eReturnCode::UNKNOWN_ERROR>;
	}
}

int handle_checksum_calculation(std::filesystem::path const& fp)
{
	if (std::filesystem::is_directory(fp))
	{
		std::cout << crc::str_dir_checksum(fp);
		
		return codes::return_code<codes::eReturnCode::SUCCESS>;
	}

	/* Open input filestream from provided file */
	std::cout << crc::str_checksum(fp) << std::endl;

	return codes::return_code<codes::eReturnCode::SUCCESS>;
}