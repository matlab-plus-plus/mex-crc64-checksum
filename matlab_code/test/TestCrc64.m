classdef TestCrc64 < matlab.unittest.TestCase
    % Tests of the functions crc64.FileChecksum, crc64.TextChecksum, and
    % crc64.FolderChecksum.
    
    properties (TestParameter)
        IODataPair = jsondecode(fileread("checksum_test_data.json"));
        OutputFormatAsHex = struct("hex", true, "int", false);
    end
    
    methods (Test)
        function TestTextChecksum(TestCase, IODataPair, OutputFormatAsHex)
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
            
            % Need to convert the expected checksum to an int if we're not
            % getting a hex string as output.
            if OutputFormatAsHex
                ExpChecksum = string(IODataPair.output_hex);
            else
                ExpChecksum = uint64(hex2int(IODataPair.output_hex));
            end
            
            ActChecksum = crc64.TextChecksum(InputText, "AsHexString", OutputFormatAsHex);
            TestCase.verifyEqual(ActChecksum, ExpChecksum)
        end
    end
end

function IntOut = hex2int(HexStr)
% Can't directly use hex2dec because it loses precision.
IntOut = bitor( ...
    bitshift(uint64(hex2dec(HexStr(1:8))), 32), ...
    uint64(hex2dec(HexStr(9:end))), ...
    'uint64' ...
);
end