function [] = fft_waterfall(power,carrier_freq,samp_freq,time_fn,figure_handle)
%FFT_WATERFALL Generates a waterfall plot for given power measurements.
%   FFT_WATERFALL(POWER) will generate plot with using matrix indices and
%   in the current figure.
%
%   FFT_WATERFALL(POWER,CARRIER_FREQ,SAMP_FREQ) will plot x-axis
%   frequency values.
%
%   FFT_WATERFALL(POWER,CARRIER_FREQ,SAMP_FREQ,TIME_FN) will plot x-axis
%   frequency values and y-axis time values.
%
%   FFT_WATERFALL(POWER,CARRIER_FREQ,SAMP_FREQ,TIME_FN,FIGURE_HANDLE) will 
%   plot axis values and plot in the given figure.
%
%   POWER is a matrix containing power calculations for FFTs in dBm.
%
%   CARRIER_FREQ is the carrier frequency of the receiver.
%
%   SAMP_FREQ is the sampling frequency of the receiver.
%
%   TIME_FN is an anonymous function that takes in the index of a given
%   FFT in the power matrix and returns the corresponding time. It can also
%   be a row vector of the same lenght as a row in POWER.
%
%   FIGURE_HANDLE is a figure handle generated using the figure function.

    narginchk(1,5);
    
    x_axis = 'Frequency (Hz)';
    y_axis = 'Approximate Time (sec)';
    
    if nargin < 5
        figure_handle = gcf;
    end
    if nargin < 4
        time_fn = @(x) x;
        y_axis = 'Time';
    end
    if nargin == 2
        error('There cannot be 2 input arguments.');
    end
    if nargin == 1
        freq_fn = @(x) x;
        x_axis = 'Frequency';
    end
    if nargin ~= 1
        freq_fn = @(x) samp_freq/numel(power(1,:)).*x + carrier_freq - samp_freq/2;
    end
    
    figure(figure_handle);
    imagesc(freq_fn(1:numel(power(1,:))),time_fn(1:numel(power(:,1))),power);
    title('Waterfall Plot');
    xlabel(x_axis);
    ylabel(y_axis);
    c = colorbar;
    ylabel(c, 'Power (dBm)');
end    