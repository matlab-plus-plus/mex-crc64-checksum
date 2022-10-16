/*
* Checksum formatting
*/

#pragma once

#include "crc.hpp"

#include <string>

namespace crc::_internal
{
	std::string format_checksum(crc::checksum_t const);
}