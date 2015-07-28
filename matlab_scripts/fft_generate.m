function [ffts] = fft_generate(time_samps,fft_size,overlap,window)
%FFT_GENERATE Generates a matrix of FFTs from given time samples.
%   FFT_GENERATE(TIME_SAMPS,FFT_SIZE,OVERLAP,WINDOW) will create a
%   matrix of FFTs from the given time samples.
%   
%   TIME_SAMPS is a row vector of complex time samples.
%
%   FFT_SIZE is the number of samples per FFT.
%
%   OVERLAP specifies the amount of overlap between consecutive FFTs.
%
%   WINDOW is a row vector of size FFT_SIZE that will be applied as a 
%   window functionto the time samples before generating FFTs.

    if fft_size < 1
        error('The FFT size must be at least 1.');
    elseif overlap < 0 || overlap > 1
        error('Overlap must be a value between 0 and 1, inclusive.');
    elseif any(size(window) ~= [1 fft_size])
        error('Window must be a row vector of length fft_size.');
    end

    o = 1-overlap;
    fft_size = floor(fft_size);
    N = numel(time_samps);

    start = @(x) ceil(fft_size*o.*x+1);         % beginning of each FFT
    stop = @(x) start(x) + fft_size-1;          % end of each FFT

    ffts = [];
    i = 0;
    while stop(i) <= numel(time_samps)
        sample = time_samps(start(i):stop(i));
        ffts = [ ffts ; fftshift( fft( sample.*window , fft_size ) ) ];
        i = i+1;
    end
    
end