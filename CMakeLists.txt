cmake_minimum_required(VERSION 3.20)
project(crc64 VERSION 1.0.0)

add_subdirectory("../LFSRLib/" "${CMAKE_SOURCE_DIR}/ext/lfsrlib")

#set(Boost_DIR C:/Sandbox/CPP_Libs/boost_1_78_0/tools/boost_install)
set(Boost_INCLUDE_DIR C:/Sandbox/CPP_Libs/boost_1_78_0)
set(Boost_LIBRARY_DIR C:/Sandbox/CPP_Libs/boost_1_78_0/libs)
find_package(Boost 1.78 REQUIRED)

add_executable(crc64)
#target_link_libraries(crc64 lfsr_lib)
#target_link_libraries(crc64 Boost::crc)

set_target_properties( crc64
    PROPERTIES
	CXX_STANDARD 23
)

target_sources(
	crc64
	PRIVATE "./inc/crc.hpp"
	        "./src/main.cpp"
			"./src/crc.cpp"
			"./inc/application/codes.hpp"
			"C:/Sandbox/CPP_Libs/boost_1_78_0/boost/crc.hpp"
)

target_include_directories(
	crc64
	PRIVATE "./inc"
	        "C:/Sandbox/CPP_Libs/boost_1_78_0"
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
			"C:/Sandbox/CPP_Libs/boost_1_78_0"
)

target_sources(
	crc_mex
	PRIVATE "./inc/crc.hpp"
	        "./src/crc_mex.cpp"
			"./src/crc.cpp"
			"./inc/application/codes.hpp"
			"C:/Sandbox/CPP_Libs/boost_1_78_0/boost/crc.hpp"
)

set_target_properties( crc_mex
    PROPERTIES
	CXX_STANDARD 23
)

install(TARGETS crc64 crc_mex)