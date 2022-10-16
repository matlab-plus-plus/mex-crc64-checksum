/*
* Internal code for computing the checksum of a directory.
*/

#pragma once

#include "crc.hpp"

#include <filesystem>
#include <string>

namespace crc
{
	std::string str_dir_checksum(std::filesystem::path const);
	checksum_t calc_dir_checksum(std::filesystem::path const);
}