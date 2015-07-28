#ifndef SPECTRO_H
#define SPECTRO_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <fftw3.h>
#include <gnuplot-iostream.h>
using namespace std;

// iq_samples = row matrix (vector) of IQ samples
// carrier_freq = carrier frequency
// sampling_freq = sampling frequency
// fft_size = size of FFTs
// overlap = overlap between FFTs (between 0 and 1)
// window = row matrix (vector) of size k to be used as a window function
// average_ffts = number of ffts to be averaged together

class fft_avg {
 private:
  vector<complex<double> > iq_samples_;
  double carrier_freq_;
  double sampling_freq_; 
  unsigned int fft_size_;
  double overlap_; 
  vector<complex<double> > window_; 
  unsigned int average_ffts_;
  fftw_complex *in_;
  fftw_complex *out_;
  fftw_plan plan_;
  //vector<complex<double> > mags_;
  vector<vector<double> > fft_data_;
public:
// beginning of each FFT
  unsigned int start(int index, unsigned int fft_size, double overlap);
// end of each FFT
  unsigned int stop(int index, unsigned int fft_size, double overlap);

  void spectro();
  vector<vector<double> >* get_fft_data() {
  	return &fft_data_;
  }

  fft_avg() {}
  fft_avg(vector<complex<double> > iq_samples, double carrier_freq, 
  	     double sampling_freq, unsigned int fft_size, double overlap, 
  	     vector<complex<double> > window, unsigned int average_ffts); 

  ~fft_avg();



};

#endif