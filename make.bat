@echo off
pushd "%~dp0\out"

cmake.exe -S .. -B .

cmake.exe --build .

popd