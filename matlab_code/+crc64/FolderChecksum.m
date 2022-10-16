function ChkSum = FolderChecksum(Folder, Params)
% Computes CRC64 checksum of a folder.
arguments
    Folder (1,:) char {mustBeFolder};
    Params.AsHexString (1,1) logical = false;
end

ChkSum = crc64(2, Folder);

if Params.AsHexString
    ChkSum = toHexString(ChkSum);
end

end