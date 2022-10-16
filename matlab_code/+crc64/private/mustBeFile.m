function mustBeFile(FileCandidate)
if ~isfile(FileCandidate)
    throwAsCaller(MException(mfilename() + ":InputNotFile", ...
        "Input value '%s' was supposed to be a file but was not.", ...
        FileCandidate));
end
end