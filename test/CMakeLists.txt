# Tests for crc64

cmake_minimum_required(VERSION 3.22)
project(crc64_tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST_DRIVER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test-driver.bat)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# So that GoogleTest does not get installed with this project
option(INSTALL_GTEST "Enable installation of googletest." OFF)

FetchContent_MakeAvailable(googletest)

add_test(
	NAME f_empty
	COMMAND ${TEST_DRIVER_PATH} $<TARGET_FILE:crc64> empty.txt 0000000000000000
)

add_test(
	NAME f_check
	COMMAND ${TEST_DRIVER_PATH} $<TARGET_FILE:crc64> check.txt 995DC9BBDF1939FA
)

add_test(
	NAME f_check_reverse
	COMMAND ${TEST_DRIVER_PATH} $<TARGET_FILE:crc64> check-reverse.txt E7ADEF3D663C7E22
)

add_test(
	NAME f_eight_ones
	COMMAND ${TEST_DRIVER_PATH} $<TARGET_FILE:crc64> eight-ones.txt A05AC6AA26A9F8B1
)

add_test(
	NAME f_eight_zeros
	COMMAND ${TEST_DRIVER_PATH} $<TARGET_FILE:crc64> eight-zeros.txt A080A25B7830E6F0
)

add_test(
	NAME f_keyboardmash
	COMMAND ${TEST_DRIVER_PATH} $<TARGET_FILE:crc64> keyboardmash.txt 3D8A249DEA572D65
)

add_test(
	NAME f_maxbyte_1
	COMMAND ${TEST_DRIVER_PATH} $<TARGET_FILE:crc64> maxbyte-1.txt 37CD8DBE8B066477
)

add_test(
	NAME f_null_sequence_1
	COMMAND ${TEST_DRIVER_PATH} $<TARGET_FILE:crc64> null-sequence-1.dat 14A6C721506FB0F0
)

add_test(
	NAME f_test_bin
	COMMAND ${TEST_DRIVER_PATH} $<TARGET_FILE:crc64> test-bin.exe DD9ACD49D90CE187
)

add_test(
	NAME f_test
	COMMAND ${TEST_DRIVER_PATH} $<TARGET_FILE:crc64> test.txt DD9ACD49D90CE187
)

add_library(file_util_lib STATIC)
target_sources(
	file_util_lib
	PUBLIC  ./src/fileutil.hpp
	PRIVATE ./src/fileutil.cpp
	        ./src/private_fileutil_windows.hpp
)
target_include_directories(
	file_util_lib
	PUBLIC ./src/
)
target_link_libraries(
	file_util_lib
	PRIVATE long_path_util
)

add_executable(
	hang_test
	./src/hang_test.cpp
)
target_link_libraries(
	hang_test
	PRIVATE crc64_lib
	        file_util_lib
			GTest::gtest_main
)

include(GoogleTest)
# We need to limit the time for the hang tests because by definition,
# they catch bugs where the program hangs.
gtest_discover_tests(
	hang_test
	PROPERTIES TIMEOUT 0.2
)