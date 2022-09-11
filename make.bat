@echo off

set CFG_NAME=%1
if "%CFG_NAME%" == "" (
	set CFG_NAME=Debug
)

pushd %~dp0
cmake.exe -S . -B ./out
cmake.exe --build ./out --config %CFG_NAME%
cmake.exe --install ./out --prefix . --config %CFG_NAME%
popd
