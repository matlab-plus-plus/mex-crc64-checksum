# Tests for crc64

cmake_minimum_required(VERSION 3.22)
project(crc64_tests)

cmake_path(NATIVE_PATH CMAKE_CURRENT_SOURCE_DIR TEST_DATA_FILE_DIR)
set(TEST_DRIVER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test-driver.bat)

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