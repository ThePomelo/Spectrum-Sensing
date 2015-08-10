function [fft_data] = spectro(filename,carrier_freq,samp_freq,fft_size,overlap,window,average_size)
%SPECTRO Frequency analysis.
%   SPECTRO(FILENAME) reads in preprocessed FFT data and plots it.
%
%   SPECTRO(FILENAME,CARRIER_FREQ,SAMP_FREQ,FFT_SIZE,OVERLAP,WINDOW,AVERAGE_SIZE)
%   analyzes time sample data and generates visuals in frequency domain.
%   
%   FILENAME is the name of the file containing raw IQ time samples or 
%   preprocessed FFT data.
%
%   CARRIER_FREQ is the receiver carrier frequency.
%
%   SAMP_FREQ is the receiver sampling frequency.
%
%   FFT_SIZE is the size of FFT samples.
%
%   OVERLAP is the percent, between 0 and 1, of overlap between FFTs.
%
%   WINDOW is a row vector of size FFT_SIZE to be used as a window
%   function in FFT generation.
%
%   AVERAGE_SIZE is the number of FFTs to be averaged in the moving
%   average filter.

    if nargin ~= 1 && nargin ~= 7
        error('There must be either 1 or 7 input arguments.');
    elseif nargin == 1
    elseif carrier_freq <= 0
        error('Carrier frequency must be a positive value in Hz.');
    elseif samp_freq <= 0
        error('Samplng frequency must be a positive value in Hz.');
    elseif fft_size < 1
        error('The FFT size must be at least 1.');
    elseif overlap < 0 || overlap > 1
        error('Overlap must be a value between 0 and 1, inclusive.');
    elseif any(size(window) ~= [1 fft_size])
        error('Window must be a row vector of length fft_size.');
    elseif average_size < 1
        error('Average size must be at least 1');
    end


    if nargin == 1 % Preprocessed data
        fft_data = dlmread(filename, ' ', 10, 1);
        fft_data(all(fft_data <= 0,2),:) = [];
        fft_data(:,~all(fft_data)) = [];
        figure(1);
        fft_waterfall(20*log10(fft_data/1000.0));
        return
    end
    

    fft_size = floor(fft_size);
    average_size = floor(average_size);

    fprintf('Reading Time Samples ... ');
    time_samps = readsamples(filename);
    fprintf('Done.\n');

    
    N = numel(time_samps);

    fprintf('Generating FFTs ... ');
    fft_data = fft_generate(time_samps,fft_size,overlap,window);
    fprintf('Done.\n');


    if average_size ~= 1
        fprintf('Averaging FFTs ... ');
    end
    magnitudes = fft_moving_avg(abs(fft_data),average_size);
    if average_size ~= 1
        fprintf('Done.\n');
    end

    
    fprintf('Calculating Power ... ');
    power = 20*log(magnitudes/1000.0);
    fprintf('Done.\n');
    
    
    get_time = @(x) numel(time_samps)/samp_freq/numel(power(:,1)).*(x-1);
    
    fprintf('Generating Waterfall Plot ... ');
    fft_waterfall(power,carrier_freq,samp_freq,get_time,figure(1));
    fprintf('Done.\n');
    
    
    fprintf('Plotting FFTs and Finding Peaks... ');
    fft_peaks(power,carrier_freq,samp_freq,get_time,figure(2));
    fprintf('Done.\n');
end
    