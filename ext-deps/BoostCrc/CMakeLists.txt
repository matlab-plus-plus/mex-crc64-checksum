# Pull the Boost dependencies needed for the CRC library

cmake_minimum_required(VERSION 3.22)
project(boost_crc)

include(FetchContent)

set(BOOST_VERSION boost-1.78.0)

function(fetch_boost_lib BSTLIB)
	fetchcontent_declare(
		Boost-${BSTLIB}
		GIT_REPOSITORY https://github.com/boostorg/${BSTLIB}.git
		GIT_TAG ${BOOST_VERSION}
	)
	fetchcontent_makeavailable(Boost-${BSTLIB})
endfunction()

# Fetch the CRC Boost library
fetchcontent_declare(
	BoostCRC
	GIT_REPOSITORY https://github.com/boostorg/crc.git
	GIT_TAG ${BOOST_VERSION}
)

# crc is the only library we care about, but it imposes transitive dependencies
fetch_boost_lib(array)
   fetch_boost_lib(assert)
   fetch_boost_lib(core)
   fetch_boost_lib(static_assert)
   fetch_boost_lib(throw_exception)
fetch_boost_lib(config)
fetch_boost_lib(integer)
fetch_boost_lib(type_traits)

# Make BoostCRC available by invoking the CMake command
fetchcontent_makeavailable(
	BoostCRC
)