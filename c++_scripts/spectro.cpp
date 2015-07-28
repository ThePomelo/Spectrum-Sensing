
// Spectrogram function implemented in C++
// Create a spectrogram of the given time-domain signal

#include <iostream>
#include <algorithm>
#include <vector>
#include <complex>
#include <fftw3.h>
#include <iterator>
#include <cmath>
#include "spectro.h"
#include <gnuplot-iostream.h>
using namespace std;

// iq_samples = row matrix (vector) of IQ samples
// carrier_freq = carrier frequency
// sampling_freq = sampling frequency
// fft_size = size of FFTs
// overlap = overlap between FFTs (between 0 and 1)
// window = row matrix (vector) of size k to be used as a window function
// average_ffts = number of ffts to be averaged together

//FFT_function::FFT_function() {
//	first_run = true;
//}
fft_avg::fft_avg(vector<complex<double> > iq_samples, double carrier_freq, 
  	     double sampling_freq, unsigned int fft_size, double overlap, 
  	     vector<complex<double> > window, unsigned int average_ffts) {

	iq_samples_ = iq_samples;
	carrier_freq_ = carrier_freq;
	sampling_freq_ = sampling_freq;
	fft_size_ = fft_size;
	overlap_ = overlap;
	window_ = window;
	average_ffts_ = average_ffts;
	/*in_ = in;
	out_ = out;
	plan_ = plan;
	empty_vector_ = empty_vector;
	fft_data_ = fft_data;*/
}
fft_avg::~fft_avg() {
	fftw_destroy_plan(plan_);
	fftw_free(in_);
	fftw_free(out_);
}

// beginning of each FFT
unsigned int fft_avg::start(int index, unsigned int fft_size, double overlap) {
	return fft_size_*overlap_*index;
}

// end of each FFT
unsigned int fft_avg::stop(int index, unsigned int fft_size, double overlap) {
	return fft_size_*overlap_*index + fft_size_ -1;//start(index, fft_size_, overlap_) + fft_size_ - 1;
}
//spectrogram function 
void fft_avg::spectro() { //unsigned int average_ffts) {

/*vector<complex<float> > iq_samples, double carrier_freq, 
  	          double sampling_freq, unsigned int fft_size, double overlap, 
  	          vector<complex<float> > window */

overlap_ = 1-overlap_;
unsigned int N = iq_samples_.size();
int index = 0;

cout<<"Generating FFTs ... ";
vector<complex<double> > s;
vector<complex<double> > s2;
s2.resize(fft_size_,0);
s.resize(fft_size_,0);
// implement fft in c++
//mags_.resize(fft_size_,0);
//fft_data_.resize(fft_size_,0);

//out_ = (fftw_complex*) &empty_vector_.front();

//plan_ = fftw_plan_dft_1d(fft_size_, in_, out_, FFTW_FORWARD, FFTW_ESTIMATE);

in_ = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*fft_size_);
out_ = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*fft_size_);
plan_ = fftw_plan_dft_1d(fft_size_, in_, out_, FFTW_FORWARD, FFTW_ESTIMATE);

fft_data_.clear();

while (stop(index, fft_size_ , overlap_) < N) {
	//cout << "start: " << start(index, fft_size_, overlap_) << endl;
	//cout << "stop: " << stop(index, fft_size_, overlap_) << endl;
	for(unsigned int i = start(index, fft_size_, overlap_); i <= stop(index, fft_size_, overlap_); i++) {
		s.at(i-start(index, fft_size_, overlap_)) = iq_samples_.at(i);
	}
	for (unsigned int i = 0; i < fft_size_; i++){
		s2.at(i) = (window_.at(i))*(s.at(i));
	}
	for (unsigned int i = 0; i < fft_size_; i++){
		in_[i][0] = s2[i].real();
		in_[i][1] = s2[i].imag();
	}
	fftw_execute(plan_);

	unsigned int fft_half = fft_size_/2;
	if (fft_size_ % 2 == 1) {
		fft_half++;
	}
	fft_data_.push_back(vector<double> ());
	auto I = fft_data_.end() - 1;

	for (unsigned int i = fft_half; i < fft_size_; i++) {
    //mags_.at(j) += sqrt(pow(out_[i][0],2) + pow(out_[i][1],2)); // the abs() here takes the sqrt as well
	I->push_back(sqrt(pow(out_[i][0],2) + pow(out_[i][1],2)));
    }
    for (unsigned int i = 0; i < fft_half; i++){
    I->push_back(sqrt(pow(out_[i][0],2) + pow(out_[i][1],2)));
    }
    /*for (int i = 0; i < fft_size_; i++) {
    	cout<<"fft_data_[" << i << "]: "<<fft_data_.at(i)<<endl;
    }*/
    //fft_data_.push_back(mags_);
	// implement fftshift in c++

	//in_ = (fftw_complex*) &(s2.front()); // THIS IS THE PROBLEM!!!!
	//fftw_execute(plan_);
	//fft_data_.push_back(empty_vector_);

// implement fftshift in c++
	/*for(int i = 0; i<s2.size(); i++) {
		cout<<"s2[" << i << "]: "<<s2.at(i)<<endl;
	}*/
	/*for(int i = 0; i<fft_size_; i++) {
		cout<<"real[" << i << "]: "<<out_[i][0]<<endl;
		cout<<"imaginary[" << i << "]: "<<out_[i][1]<<endl;
	}*/

	
	//cout<<"end of s"<<endl;
	index++;
}
cout<<"Done"<<endl;



}


