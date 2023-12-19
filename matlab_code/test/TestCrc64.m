classdef TestCrc64 < matlab.unittest.TestCase
    % Tests of the functions crc64.FileChecksum, crc64.TextChecksum, and
    % crc64.FolderChecksum.
    
    properties (TestParameter)
        IODataPair = jsondecode(fileread("checksum_test_data.json"));
    end
    
    methods (Test)
        function TestTextChecksum(TestCase, IODataPair)
            import matlab.unittest.constraints.HasField
            
            TestCase.assumeThat(IODataPair, HasField("input_text") | HasField("input_file"), ...
                "Test parameter must provide the input either directly or through a file.");
            
            % Text content containing null characters cannot be directly
            % read-in through the .json interface because it is interpreted
            % as null-termination, so we will need to read some data from
            % files.
            if isfield(IODataPair, "input_file")
                InputText = fileread(IODataPair.input_file);
            else
                InputText = IODataPair.input_text;
            end
            
            ActChecksum = crc64.TextChecksum(InputText, "AsHexString", true);
            TestCase.verifyEqual(ActChecksum, string(IODataPair.output_hex))
        end
    end
end