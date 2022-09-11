@echo off

set szipcmd="C:\Program Files\7-Zip\7z.exe" h -scrcCRC64
set mycmd="C:\Sandbox\CPP\crc64\bin\Debug\crc64.exe"

%szipcmd% "%~1"
%mycmd% "%~1"