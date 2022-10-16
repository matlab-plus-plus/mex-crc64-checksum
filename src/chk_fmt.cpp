#include "private/chk_fmt.hpp"

#include <format>

namespace crc::_internal
{
	std::string format_checksum(crc::checksum_t const csum)
	{
		return std::format("{:016X}", csum);
	}
}