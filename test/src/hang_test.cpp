#include "crc.hpp"

#include "fileutil.hpp"
#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <string_view>

// Create fixture for temporary file creation
class TempFolderTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		tempFolder = std::filesystem::temp_directory_path();

		{
			char const* tmpFolderStemName = tmpnam(nullptr);
			tempFolder /= tmpFolderStemName;
			delete tmpFolderStemName;
		}

		std::filesystem::create_directory(tempFolder);
	}

	void TearDown() override
	{
		// Delete the directory we created during setup and everything inside.
		std::filesystem::remove_all(tempFolder);
	}

	std::filesystem::path tempFolder;
};

// Ensure test does not hang when getting checksum of a nonexistent file.
TEST(HangTest, TryReadNonexistentFile)
{
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

// Ensure test does not hang when getting checksum of an already-opened file.
TEST_F(TempFolderTest, TryReadAlreadyOpenedFile)
{
	auto const test_file = tempFolder / "test.txt";
	
	auto scoped_file_lock = fileutil::file_hold_token::create(test_file);

	ASSERT_TRUE(std::filesystem::exists(test_file)) << "File should exist because we just created it.";

	constexpr auto fset{ std::ios::binary | std::ios::out };
	auto file_open_second_attempt = std::ifstream(test_file, fset);

	ASSERT_FALSE(file_open_second_attempt.good()) << "File should not be able to be opened the second time because it is already opened.";

	crc::checksum_t const actVal{ crc::calc_checksum(file_open_second_attempt) };

}

// Ensure test does not hang when trying to open a really long file path (>260 characters)
TEST_F(TempFolderTest, TryReadReallyLongFile)
{
	// Long file name generated as a random 257-character string on https://codebeautify.org/generate-random-string
	auto const test_file = tempFolder / "GavlYgaFOHJtFmcx2QW55TbyVpd0l1dgeUDpX63MID561gnNzg9dJP844PhxtvQbUHJOcPPeeJFidFg6NzTvNLa9jZE7e5kWAKaaGvGtoedulyyBULPwEHhttYqYJDepO5vfgppQG589jj4zIlGGFyFVEdroouxQTos4eVTDz5ObcTlb3paPPTuMbjPa3hVwn5iuyDt35iM7popWdoMGXrcpABS3U6kPl4ywx3micjrXNXRSQepDegAYskxD3VzCz";
	auto const test_file_safe_path = fileutil::windows_long_path_prefix / test_file;
	fileutil::create_file(test_file_safe_path);
	ASSERT_TRUE(std::filesystem::exists(test_file_safe_path)) << "Failed to create long file.";
}

// Ensure test does not hang when trying to read a file with a tilde in the name.
TEST_F(TempFolderTest, TryReadFileWithTildeInName)
{
	auto const test_file = tempFolder / std::filesystem::path("~testfile.txt");
	fileutil::create_file(test_file, "dlfsoboiregnjrng");
	ASSERT_TRUE(std::filesystem::exists(test_file)) << "Failed to create file with tilde in the name.";

	constexpr auto fset{ std::ios::binary | std::ios::out };

	auto file_open_attempt = std::ifstream(test_file, fset);
	crc::checksum_t const actVal{ crc::calc_checksum(file_open_attempt) };
}
