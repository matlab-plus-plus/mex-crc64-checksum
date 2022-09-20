/*
* External definition
*/

#pragma once

#include "boost/crc.hpp"

namespace crc::ext
{
	// CRC-64/XZ from https://reveng.sourceforge.io/crc-catalogue/all.htm
	using boost_crc64 = boost::crc_optimal< 64, 0x42f0e1eba9ea3693, 0xffffffffffffffff, 0xffffffffffffffff, true, true >;
}