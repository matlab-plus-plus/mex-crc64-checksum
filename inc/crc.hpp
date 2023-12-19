#pragma once

#include <filesystem>
#include <istream>
#include <stdexcept>
#include <string>
#include <string_view>

namespace crc
{
	using checksum_t = unsigned long long;

	std::string str_checksum(std::filesystem::path const&);
	std::string str_checksum(std::istream&);

	checksum_t calc_checksum(std::filesystem::path const&);
	checksum_t calc_checksum(std::istream&);
	checksum_t calc_checksum(std::string_view) noexcept;

	class invalid_stream_error : public std::runtime_error
	{
	public:
		explicit invalid_stream_error(std::string const&);
	};

	class file_open_error : public std::exception
	{
		std::string msg;
	public:
		explicit file_open_error(std::filesystem::path const&);
		const char* what(void) const noexcept override;
	};
}