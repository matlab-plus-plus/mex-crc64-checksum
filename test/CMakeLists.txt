# Tests for crc64

cmake_minimum_required(VERSION 3.22)
project(crc64_tests)

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
	COMMAND ${TEST_DRIVER_PATH} $<TARGET_FILE:crc64> maxbyte-1.txt F4726F40A31384BC
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