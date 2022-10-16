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
	COMMAND $<TARGET_FILE:crc64> ${TEST_DATA_FILE_DIR}\\check.txt | findstr "^995DC9BBDF1939FA$"
)

add_test(
	NAME f_check_reverse
	COMMAND $<TARGET_FILE:crc64> ${TEST_DATA_FILE_DIR}\\check-reverse.txt | findstr "^E7ADEF3D663C7E22$"
)

add_test(
	NAME f_eight_ones
	COMMAND $<TARGET_FILE:crc64> ${TEST_DATA_FILE_DIR}\\eight-ones.txt | findstr "^E7ADEF3D663C7E22$"
)