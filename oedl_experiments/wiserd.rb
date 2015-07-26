# Taken from the Spectrum sensing with USRP2 and wiserd (OEDL and OML) tutorial.

defApplication('test:app:wiserd', 'wiserd') do |a|

  a.path = "/usr/bin/wiserd"
  a.version(1, 0, 0)
  a.shortDescription = "WiSER Daemon"
  a.description = "Spectrum sensing daemon"

  # Define the properties that can be configured for this application
  # 
  # syntax: defProperty(name = :mandatory, description = nil, parameter = nil, options = {})
  #
  a.defProperty('--uhd_rx_antenna', 'Receiver antenna (''RX2'', ''TX/RX'')', '--uhd_rx_antenna', {:type => :string, :dynamic => true})
  a.defProperty('--uhd_rx_freq', 'Receiver frequency', '--uhd_rx_freq', {:type => :string, :dynamic => true})
  a.defProperty('--uhd_rx_rate', 'Receiver sampling rate', '--uhd_rx_rate', {:type => :string, :dynamic => true})
  a.defProperty('--uhd_rx_gain', 'Receiver gain in dB', '--uhd_rx_gain', {:type => :string, :dynamic => true})
  a.defProperty('--uhd_rx_bandwidth', 'Receiver bandwidth', '--uhd_rx_bandwidth', {:type => :string, :dynamic => true})
  a.defProperty('--uhd_tx_antenna', 'Transmitter antenna (''TX/RX'')', '--uhd_tx_antenna', {:type => :string, :dynamic => true})
  a.defProperty('--uhd_tx_freq', 'Transmitter frequency', '--uhd_tx_freq', {:type => :string, :dynamic => true})
  a.defProperty('--uhd_tx_rate', 'Transmitter sampling rate', '--uhd_tx_rate', {:type => :string, :dynamic => true})
  a.defProperty('--uhd_tx_gain', 'Transmitter gain in dB', '--uhd_tx_gain', {:type => :string, :dynamic => true})
  a.defProperty('--uhd_tx_bandwidth', 'Transmitter bandwidth', '--uhd_tx_bandwidth', {:type => :string, :dynamic => true})
  a.defProperty('--recv_numbins', 'Number of FFT bins', '--recv_numbins', {:type => :string, :dynamic => true})
  a.defProperty('--recv_avgwinlen', 'Average window length', '--recv_avgwinlen', {:type => :string, :dynamic => true})
  a.defProperty('--recv_oml_filename', 'Output filename for OML', '--recv_oml_filename', {:type => :string, :dynamic => true})
  a.defProperty('--recv_oml_servername', 'OML server name (''idb2:3003'', ''file'')', '--recv_oml_servername', {:type => :string, :dynamic => true})
  a.defProperty('--recv_oml_output_type', 'Output data type for OML (''blob'', ''vector'', ''scalars'')', '--recv_oml_output_type', {:type => :string, :dynamic => true})
  a.defProperty('--recv_udp_port', 'UDP port the scanning results will be streamed to', '--recv_udp_port', {:type => :string, :dynamic => true})
  a.defProperty('--recv_udp_uri', 'UDP uri the scanning results will be streamed to', '--recv_udp_uri', {:type => :string, :dynamic => true})
  a.defProperty('--recv_min_power', 'Minimal considered power in dBm for power scanning modules', '--recv_min_power', {:type => :string, :dynamic => true})
  a.defProperty('--recv_max_power', 'Maximal considered power in dBm for power scanning modules', '--recv_max_power', {:type => :string, :dynamic => true})
  a.defProperty('--recv_output_filename', 'Filename for local storing of scanning results (do not add the extension)', '--recv_output_filename', {:type => :string, :dynamic => true})
  a.defProperty('--recv_running_time', 'Running time for timed modules, in milliseconds', '--recv_running_time', {:type => :string, :dynamic => true})
  a.defProperty('--tran_wavetype', 'Type of the transmitted waveform (''SINE'', ''CONST'', ''RAMP'', ''SQUARE'')', '--tran_wavetype', {:type => :string, :dynamic => true})
  a.defProperty('--tran_wavefreq', 'Frequency of the transmitted waveform', '--tran_wavefreq', {:type => :string, :dynamic => true})
  a.defProperty('--tran_amplitude', 'Amplitude of the transmitted waveform (max 0.7)', '--tran_amplitude', {:type => :string, :dynamic => true})
  a.defProperty('--tran_wavefilename', 'Name of the file that contains the waveform', '--tran_wavefilename', {:type => :string, :dynamic => true})
  a.defProperty('--tran_running time', 'Running time for timed modules, in milliseconds', '--tran_running_time', {:type => :string, :dynamic => true})
  a.defProperty('--addmodule', 'Add a module', '--addmodule', {:type => :string, :dynamic => true})
  a.defProperty('--delmodule', 'Delete a module', '--delmodule', {:type => :string, :dynamic => true})

  # Define the Measurement Points and associated metrics that are available for this application
  #
end
