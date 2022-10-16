function mustBeFolder(FolderCandidate)
if ~isfolder(FolderCandidate)
    throwAsCaller(MException(mfilename() + ":InputNotFolder", ...
        "Input value '%s' was supposed to be a folder but was not.", ...
        FolderCandidate));
end
end