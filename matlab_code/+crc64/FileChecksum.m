function ChkSum = FileChecksum(File, Params)
% Computes CRC64 checksum of a file.
arguments
    File (1,:) char {mustBeFile};
    Params.AsHexString (1,1) logical = false;
end

ChkSum = crc64(0, File);

if Params.AsHexString
    ChkSum = toHexString(ChkSum);
end

end