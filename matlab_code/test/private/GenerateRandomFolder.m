function Ntotal = GenerateRandomFolder(Root, MaxDepth, Params)
    % Recursively generates a random folder with the given characteristics.
    
    arguments
        Root (1,1) string % Root folder
        MaxDepth (1,1) uint8 % Maximum folder depth
        Params.MinBreadth (1,1) uint8 = 2; % Minimum number of items in a folder
        Params.MaxBreadth (1,1) uint8 = 10; % Maximum number of items in a folder
        Params.MaxFileSize (1,1) uint16 = 1024; % Maximum number of bytes in a file
        Params.FolderToFileRatio (1,1) double ....
            {mustBeNonnegative, mustBeLessThanOrEqual(Params.FolderToFileRatio,1)} ...
            = 1/3; % Ratio of folders to files
        Params.RandomStream (1,1) RandStream = RandStream.create("threefry4x64_20", "Seed", 31415); % Object providing random numbers
    end
    
    % Return if we've reached our stopping condition (recursive base case).
    if MaxDepth <= 0
        Ntotal = 0;
        return
    end
    
    FwdArg = namedargs2cell(Params);
    
    % Determine number of elements in this folder
    Ne = Params.RandomStream.randi([Params.MinBreadth Params.MaxBreadth]);
    
    % Determine which of these is a folder or file
    IsDir = Params.RandomStream.rand(1, Ne) < Params.FolderToFileRatio;
    
    Ntotal = sum(~IsDir);
    
    % Create the files and folders (recursively)
    for iName = 1:Ne
        ThisName = tempname(Root);
        
        if IsDir(iName)
            mkdir(ThisName);
            Ntotal = Ntotal + GenerateRandomFolder(ThisName, MaxDepth - 1, FwdArg{:});
        else
            GenerateRandomFile(ThisName, Params);
        end
    end
end

function GenerateRandomFile(Name, Params)
fid = fopen(Name, "w");
cleanClose = onCleanup(@() fclose(fid));

Nbytes = Params.RandomStream.randi(Params.MaxFileSize, [1 1]);
Content = char(Params.RandomStream.randi(255, [1 Nbytes]));
fwrite(fid, Content);
end