function [] = fft_peaks(power,carrier_freq,samp_freq,time_fn,figure_handle)
%FFT_PEAKS Plot power vs. frequency for an FFT and find where peaks occur.
%   FFT_PEAKS(POWER,CARRIER_FREQ,SAMP_FREQ) will plot the FFT and find
%   the frequencies at which possible peaks occur.
%
%   FFT_PEAKS(POWER,CARRIER_FREQ,SAMP_FREQ,TIME_FN) will display the time
%   of each FFT.
%
%   FFT_PEAKS(POWER,CARRIER_FREQ,SAMP_FREQ,TIME_FN,FIGURE_HANDLE) will do 
%   the above operations in the given figure.
%
%   POWER is matrix containing power calculations for FFTs in dBm.
%
%   CARRIER_FREQ is the carrier frequency of the receiver.
%
%   SAMP_FREQ is the sampling frequency of the receiver.
%
%   TIME_FN is an anonymous function that takes in the index of a given
%   FFT in the power matrix and returns the corresponding time. It can also
%   be a row vector of the same lenght as a row in POWER.
%
%   FIGURE_HANDLE is a figure handle generated using the figure funtion.

    narginchk(3,5);
    
    if nargin < 5
        figure_handle = gcf;
    end
    
    freq_fn = @(x) samp_freq/numel(power(1,:)).*x + carrier_freq - samp_freq/2;
    
    x_min = carrier_freq - samp_freq/2;
    x_max = carrier_freq + samp_freq/2;
    y_min = 10*floor(min(min(power/10)));
    y_max = 10*ceil(max(max(power/10)));
    
    i = 1;
    for each_fft = power'
        figure(figure_handle);
        
        subplot(1,2,1); plot(freq_fn(1:numel(each_fft)),each_fft);
        if nargin == 3
            title(['FFT: ',int2str(i)]);
        else
            title(['Approximate Time: ',num2str(time_fn(i),'%6.4f'),' sec']);
        end
        xlabel('Frequency (Hz)');
        ylabel('Power (dBm)');
        axis([x_min x_max y_min y_max]);
        
        fft_mean = mean(each_fft);
        fft_var = std(each_fft)^2;
        
        each_fft(each_fft < fft_mean + fft_var) = fft_mean;
        
        subplot(1,2,2); plot(freq_fn(1:numel(each_fft)),each_fft);
        
        peak_freqs = freq_fn(find(each_fft ~= fft_mean));
        
        %peak_freqs = round(peak_freqs,3,'significant'); %MATLAB 2015a
        order = floor(log10(carrier_freq));
        peak_freqs = 10^(order-2).*round(peak_freqs./10^(order-2));    
        peaks = unique(peak_freqs)/10^6;
        
        title(sprintf(['Possible Peaks (MHz): ',num2str(peaks')]));
        xlabel('Frequency (Hz)');
        ylabel('Power (dBm)');
        axis([x_min x_max fft_mean y_max]);
        
        i = i+1;
        pause(0.05);
    end
end