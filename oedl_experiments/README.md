# Spectrum Sensing
Development repository for the [SDR in ORBIT: Spectrum Sensing](http://www.orbit-lab.org/wiki/Other/Summer/2015/aSDR2#SDRinORBIT:SpectrumSensing) project, part of the WINLAB Summer Internship 2015.

### OEDL Experiments

##### Experiment 1

In this experiment we modify the [Spectrum sensing with USRP2 and wiserd (OEDL and OML)](http://www.orbit-lab.org/wiki/Tutorials/k0SDR/Tutorial05#SpectrumsensingwithUSRP2andwiserdOEDLandOML) tutorial.

The tutorial uses two USRPs: one transmitter and one receiver. The transmitter starts at 798 MHz and increases to 802 MHz over a span of 5 seconds. The receiver has a carrier frequency of 800 MHz and bandwidth of 5 MHz.

As our first experiment we modified the tutorial. We increase the sampling rate to 10 MHz, so we can accurately receive frequencies up to 5 MHz greater or lesser than the receiver's carrier frequency. We then randomly select frequencies from 796 to 804 MHz to transmit for one second each.

Using OML, we save the receiver readings to a file for processing in MATLAB/Octave. Using a MATLAB script, we generate a waterfall plot of the data, along with an animated power vs. frequency plot.

**Update: Raw IQ Samples and Processing in MATLAB**

Next, using the same frequencies and sampling rate as the original tutorial, we modified the OEDL script in order to collect raw time domain samples using ORBIT as opposed to samples that had already been converted into the frequency domain.

We then wrote a MATLAB script entitled "spectro" which we used to convert the raw data into the frequency domain. From there, we again generate a waterfall plot of the data.

Using the raw IQ samples instead of preprocessed FFT data allows for more flexibility in our signal processing. We now have access to a much larger collection of data, and we can produce more accurate frequency domain transforms.
