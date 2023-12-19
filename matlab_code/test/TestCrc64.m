classdef TestCrc64 < matlab.unittest.TestCase
    % Tests of the functions crc64.FileChecksum, crc64.TextChecksum, and
    % crc64.FolderChecksum.
    
    properties (Access = private)
        WorkingFolder (1,1) string;
    end
    
    properties (TestParameter)
        IODataPair = jsondecode(fileread(fullfile("private", "checksum_test_data.json")));
        OutputFormatAsHex = struct("hex", true, "int", false);
    end
    
    methods (TestClassSetup)
        function CreateTempFolder(TestCase)
            import matlab.unittest.fixtures.TemporaryFolderFixture
            
            TFF = TestCase.applyFixture(TemporaryFolderFixture());
            TestCase.WorkingFolder = TFF.Folder;
        end
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
                InputText = fileread(fullfile("private",IODataPair.input_file));
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
        
        function TestFileChecksum(TestCase, IODataPair, OutputFormatAsHex)
            import matlab.unittest.constraints.HasField
            
            TestCase.assumeThat(IODataPair, HasField("input_text") | HasField("input_file"), ...
                "Test parameter must provide the input either directly or through a file.");
            
            % Copy if input is already a file
            if isfield(IODataPair, "input_file")
                OrigFile = fullfile(fileparts(mfilename("fullpath")), "private", IODataPair.input_file);
                InputFile = TestCase.CopyFile(OrigFile);
            else
                InputFile = TestCase.CreateFile(IODataPair.input_text);
            end
            
            % Need to convert the expected checksum to an int if we're not
            % getting a hex string as output.
            if OutputFormatAsHex
                ExpChecksum = string(IODataPair.output_hex);
            else
                ExpChecksum = uint64(hex2int(IODataPair.output_hex));
            end
            
            ActChecksum = crc64.FileChecksum(InputFile, "AsHexString", OutputFormatAsHex);
            TestCase.verifyEqual(ActChecksum, ExpChecksum)
        end
        
        function TestFileChecksumThrowsWhenFileDoesNotExist(TestCase)
            import matlab.unittest.constraints.Throws
            
            TempFile = TestCase.GenNewFileName();
            
            TestCase.verifyThat(@() crc64.FileChecksum(TempFile), Throws("mustBeFile:InputNotFile"));
        end
    end
    
    methods (Access = private)
        function NewFile = CreateFile(TestCase, Text)
            NewFile = TestCase.GenNewFileName();
            filewrite(Text, NewFile);
        end
        
        function NewFile = CopyFile(TestCase, FileName)
            import matlab.unittest.constraints.IsFile
            
            TestCase.assumeThat(FileName, IsFile());
            
            NewFile = TestCase.GenNewFileName();
            copyfile(FileName, NewFile);
        end
        
        function NewFile = GenNewFileName(TestCase)
            NewFile = tempname(TestCase.WorkingFolder);
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

function filewrite(FileText, FilePath)
% Writes the text to a file
fid = fopen(FilePath, 'w');
clean_CloseFile = onCleanup(@() fclose(fid));

fwrite(fid, FileText);

end