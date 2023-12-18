classdef TestCrc64 < matlab.unittest.TestCase
    % Tests of the functions crc64.FileChecksum, crc64.TextChecksum, and
    % crc64.FolderChecksum.
    
    properties (TestParameter)
        IODataPair = jsondecode(fileread("checksum_test_data.json"));
    end
    
    methods (Test)
        function TestTextChecksum(TestCase, IODataPair)
            ActChecksum = crc64.TextChecksum(IODataPair.input_text, "AsHexString", true);
            TestCase.verifyEqual(ActChecksum, string(IODataPair.output_hex))
        end
    end
end