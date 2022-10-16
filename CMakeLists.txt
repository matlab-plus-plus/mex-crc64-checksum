cmake_minimum_required(VERSION 3.20)
project(crc64 VERSION 1.0.0)

# Enable testing
include(CTest)

add_subdirectory(./ext-deps)

add_executable(crc64)

set_target_properties( crc64
    PROPERTIES
	CXX_STANDARD 23
)

target_sources(
	crc64
	PRIVATE "./inc/crc.hpp"
	        "./inc/private/directory_checksum_mt.hpp"
			"./inc/private/chk_fmt.hpp"
			"./inc/private/ext_def.hpp"
	        "./src/main.cpp"
			"./src/crc.cpp"
			"./src/directory_checksum_mt.cpp"
			"./src/chk_fmt.cpp"
			"./inc/application/codes.hpp"
)

target_include_directories(
	crc64
	PRIVATE "./inc"
)

target_link_libraries(
	crc64
	PRIVATE Boost::crc
)

find_package(Matlab 9.8 REQUIRED)
matlab_add_mex(
	NAME crc_mex
	SHARED
	OUTPUT_NAME crc64
	R2018a
)

target_include_directories(
	crc_mex
	PRIVATE "./inc"
	        "${Matlab_INCLUDE_DIRS}"
)

target_sources(
	crc_mex
	PRIVATE "./inc/crc.hpp"
	        "./inc/private/directory_checksum_mt.hpp"
			"./inc/private/chk_fmt.hpp"
			"./inc/private/ext_def.hpp"
	        "./src/crc_mex.cpp"
			"./src/crc.cpp"
			"./src/directory_checksum_mt.cpp"
			"./src/chk_fmt.cpp"
			"./inc/application/codes.hpp"
)

set_target_properties( crc_mex
    PROPERTIES
	CXX_STANDARD 23
)

target_link_libraries(
	crc_mex
	Boost::crc # Must be public even though we would prefer private due to already using 'Plain' signature implicitly in the matlab_add_mex command
)

# Tests
add_subdirectory(./test)

install(TARGETS crc64 crc_mex)
install(TARGETS crc_mex
	RUNTIME DESTINATION ./matlab_code/+crc64/private
)