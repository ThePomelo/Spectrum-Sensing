# Experiment 1

# Based on the Spectrum sensing with USRP2 and wiserd (OEDL and OML) tutorial.

# Transmit signals of randomly selected frequencies from 796 to 804 MHz.


defProperty('rx_freq', "800e6", "")
defProperty('rx_rate', "5e6", "")
defProperty('rx_gain', "20", "")
defProperty('recv_oml_output_type', "vector", "")
defProperty('recv_oml_servername', "file", "")
defProperty('tx_freq', "800e6", "")
defProperty('tx_rate', "5e6", "")
defProperty('tx_gain', "20", "")
defProperty('tx_module', "foo", "") # using a random name for an unexisting module
defProperty('rx_module', "foo", "") # so that no module is started, but it can be added later by setting this property
defProperty('del_rx_module', "foo", "")


require './wiserd.rb'

defGroup('sender', "node1-1") do |node|
  node.addApplication("test:app:wiserd") do |app|
    app.setProperty('--uhd_tx_freq', property.tx_freq)
    app.setProperty('--uhd_tx_rate', property.tx_rate)
    app.setProperty('--uhd_tx_gain', property.tx_gain)
    app.setProperty('--addmodule', property.tx_module)
  end
end

defGroup('receiver', "node1-2") do |node|
  node.addApplication("test:app:wiserd") do |app|
    app.setProperty('--uhd_rx_freq', property.rx_freq)
    app.setProperty('--uhd_rx_rate', property.rx_rate)
    app.setProperty('--uhd_rx_gain', property.rx_gain)
    app.setProperty('--recv_oml_output_type', property.recv_oml_output_type)
    app.setProperty('--recv_oml_servername', property.recv_oml_servername)
    app.setProperty('--addmodule', property.rx_module)
    app.setProperty('--delmodule', property.del_rx_module)
  end
end

onEvent(:ALL_UP_AND_INSTALLED) do |event|
  wait 10
  info "Starting the Receiver"
  group("receiver").startApplications
  info "Starting the Sender"
  group("sender").startApplications
  wait 8
  property.tx_module = "waveform"
  property.rx_module = "timesamplestofile"
  for i in 798..802
    property.tx_freq = "#{n}e6"
    wait 1
  end
  property.del_rx_module = "timesamplestofile"
  group("sender").stopApplications
  group("receiver").stopApplications
  Experiment.done
end
