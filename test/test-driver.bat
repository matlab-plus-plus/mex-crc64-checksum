:: Runs the crc64 program against a test file and
:: compares the result to the given value. Returns
:: exit code of 0 if matching and nonzero otherwise.
@echo off

set errorlevel=
%1 %~dp0%2 | findstr "^%3$"

exit /B %errorlevel%