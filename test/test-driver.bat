:: Runs the crc64 program against a test file and
:: compares the result to the given value. Returns
:: exit code of 0 if matching and nonzero otherwise.
@echo off

:: Replace forward slashes with backslashes in the
:: path to the executable under test.
set exe_under_test=%1
set exe_under_test=%exe_under_test:/=\\%

:: Remove extra double quotes from the test data
:: input file and concatenate with parent folder.
set test_data_file=%~dp0%2
set test_data_file=%test_data_file:"=%

:: Run the executable under test and compare the
:: output with the expected value.
set errorlevel=
%exe_under_test% "%test_data_file%" | findstr /r /c:"^%3 *$" > nul

:: Return the error code given by findstr; if
:: the output from the executable under test
:: matched the expected value, the return code
:: will be 0 and ctest understands this means
:: the test passed.
exit /B %errorlevel%