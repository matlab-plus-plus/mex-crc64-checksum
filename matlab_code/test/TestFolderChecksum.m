classdef TestFolderChecksum < matlab.unittest.TestCase
    
    properties (TestParameter)
        Seed = {4168664255, 4111000739, 2084672538,3437178441, 609397185, 1811450916};
    end
    
    methods (Test)
        function TestRandomFolderChecksum(TestCase, Seed)
            import matlab.unittest.fixtures.TemporaryFolderFixture
            import matlab.unittest.constraints.IsFolder
            
            TFF = TestCase.applyFixture(TemporaryFolderFixture());
            RS = RandStream.create("threefry4x64_20", "Seed", Seed);
            NumFiles = GenerateRandomFolder(TFF.Folder, 5, "MinBreadth", 4, "MaxBreadth", 7, "RandomStream", RS);
            
            TestCase.assumeThat(TFF.Folder, IsFolder(), "Failed to generate random folder for test.");
            TestCase.log(matlab.unittest.Verbosity.Detailed, sprintf("Randomly generated folder with total of %i files", NumFiles));
            
            tstart = tic();
            ActChecksum = crc64.FolderChecksum(TFF.Folder);
            runtime = toc(tstart);
            TestCase.log(matlab.unittest.Verbosity.Detailed, sprintf("Computed folder checksum in %0.3f seconds", runtime));
        end
    end
end

