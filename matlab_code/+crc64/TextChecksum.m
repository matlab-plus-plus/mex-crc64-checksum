function ChkSum = TextChecksum(Text, Params)
% Computes CRC64 checksum of text (string or char array).
arguments
    Text (1,:) char;
    Params.AsHexString (1,1) logical = false;
end

ChkSum = crc64(1, Text);

if Params.AsHexString
    ChkSum = toHexString(ChkSum);
end

end