#include "crc.hpp"

#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

// Ensure test does not hang when getting checksum of an already-opened file.
TEST(HangTest, TryReadNonexistentFile) {
	// Open the file in another stream
	std::filesystem::path const test_file{ "sfjsdfijojeflkjdef.txt" };

	// Ensure the file exists before trying to do things with it
	ASSERT_FALSE(std::filesystem::exists(test_file)) << "Fake file '"
		<< test_file << "' should not exist because we need to make "
		<< "sure the application does not freeze when failing to open a file.";

	constexpr auto fset{ std::ifstream::binary | std::ifstream::in };
	auto file_open_attempt = std::ifstream(test_file, fset);

	// Ensure the blocking open occurred successfully
	ASSERT_FALSE(file_open_attempt.good()) << "File should not have opened for our test's sake";

	crc::checksum_t const actVal{ crc::calc_checksum(file_open_attempt) };
}
