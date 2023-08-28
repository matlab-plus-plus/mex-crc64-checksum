#pragma once

#include <filesystem>
#include <istream>
#include <string_view>

namespace crc
{
	using checksum_t = unsigned long long;

	std::string str_checksum(std::filesystem::path const);
	std::string str_checksum(std::istream&);

	checksum_t calc_checksum(std::filesystem::path const);
	checksum_t calc_checksum(std::istream&);
	checksum_t calc_checksum(std::string_view) noexcept;
}