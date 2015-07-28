function [avg_ffts] = fft_moving_avg(fft_magnitudes,average_size)
%FFT_MOVING_AVG A moving average filter for FFT data.
%   FFT_MOVING_AVG(FFT_MAGNITUDES,AVERAGE_SIZE) will apply a moving
%   average filter to the given FFT magnitudes.
%
%   FFT_MAGNITUDES is a matrix whose rows are consecutive FFT magnitudes.
%
%   FFT_SIZE is the number of FFTs to be averaged together in each
%   iteration. Must be at least 1.

    if average_size < 1
        error('Average size must be at least 1');
    end

    average_size = round(average_size);

    if average_size == 1
        avg_ffts = fft_magnitudes;
        return
    end

    avg_ffts = [];
    i = 1;
    while i < (numel(fft_magnitudes(:,1))-average_size)
        avg_sample = fft_magnitudes(i:i+average_size-1,:);
        avg_ffts = [avg_ffts;sum(avg_sample)/average_size];
        i = i+1;
    end
end

