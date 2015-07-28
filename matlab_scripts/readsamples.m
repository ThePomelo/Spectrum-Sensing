function [ samps ] = readsamples( filename )
%READSAMPLES Read in complex binary data.
%   READSAMPLES(FILENAME) will store the data in FILENAME into a row
%   vector of complex floats.
%
%   FILENAME is a string specifying the name of the file containin the
%   time samples. Must be a binary file.
    fid = fopen(filename);
    if fid == -1
        error(['Cannot read file ',filename]);
    end
%    i = 0;
%    while ~feof(fid)
%        a = fread(fid, 1, 'float32');
%        b = fread(fid, 1, 'float32');
%        if (length(a) == 1) && (length(b) == 1)
%            i = i + 1;
%            samps(i) = a + b * 1i;;
%        else
%            length(a)
%            length(b)
%        end
%    end
    %aa = fread(fid, [2, size], 'float32');
    ss = fread(fid, [2, inf], 'float32');
    samps = ss(1,:) + 1i .* ss(2,:);
    fclose(fid);
end
