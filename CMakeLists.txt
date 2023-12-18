cmake_minimum_required(VERSION 3.20)
project(crc64 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
include(CTest)

add_subdirectory(./ext-deps)

add_library(long_path_util STATIC)
target_sources(
	long_path_util
	PUBLIC  "./inc/longpath/longpath.hpp"
	PRIVATE "./src/longpath.cpp"
)
target_include_directories(
	long_path_util
	PUBLIC "./inc/longpath"
)

add_library(crc64_lib STATIC)
target_sources(
	crc64_lib
	PUBLIC "./inc/crc.hpp"
	       "./src/crc.cpp"
		   "./inc/private/directory_checksum_mt.hpp"
		   "./src/directory_checksum_mt.cpp"
           "./inc/private/chk_fmt.hpp"
	       "./src/chk_fmt.cpp"
)
target_link_libraries(
	crc64_lib
	PUBLIC Boost::crc
	       long_path_util
)
target_include_directories(
	crc64_lib
	PUBLIC "./inc"
)

add_executable(crc64)

set_target_properties( crc64
    PROPERTIES
	CXX_STANDARD 23
)

target_sources(
	crc64
	PUBLIC  "./inc/application/codes.hpp"
	PRIVATE "./src/main.cpp"
)

target_include_directories(
	crc64
	PRIVATE "./inc"
)

target_link_libraries(
	crc64
	PRIVATE crc64_lib
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
	PRIVATE "${Matlab_INCLUDE_DIRS}"
)

target_sources(
	crc_mex
	PRIVATE "./src/crc_mex.cpp"
			"./inc/application/codes.hpp"
)

set_target_properties( crc_mex
    PROPERTIES
	CXX_STANDARD 23
)

target_link_libraries(
	crc_mex
	crc64_lib # Must be public even though we would prefer private due to already using 'Plain' signature implicitly in the matlab_add_mex command
)

# Tests
add_subdirectory(./test)

install(TARGETS crc64_lib crc64 crc_mex)
install(
	DIRECTORY ./matlab_code/+crc64
			  ./matlab_code/test
	DESTINATION ./
)
install(TARGETS crc_mex
	RUNTIME DESTINATION ./+crc64/private
)