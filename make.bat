@echo off

set CFG_NAME=%1
if "%CFG_NAME%" == "" (
	set CFG_NAME=Debug
)

pushd %~dp0
cmake.exe -S . -B ./out/build
cmake.exe --build ./out/build --config %CFG_NAME%
cmake.exe --install ./out/build --prefix ./out/install --config %CFG_NAME%
popd
