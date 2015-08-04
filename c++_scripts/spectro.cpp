
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
#include "gnuplot-iostream.h"
using namespace std;

// iq_samples = row matrix (vector) of IQ samples
// carrier_freq = carrier frequency
// sampling_freq = sampling frequency
// fft_size = size of FFTs
// overlap = overlap between FFTs (between 0 and 1)
// window = row matrix (vector) of size k to be used as a window function
// average_ffts = number of ffts to be averaged together

//FFT_function::FFT_function() {
//      first_run = true;
//}
Spectro::Spectro() {
        gp << "set terminal x11\n";
}

Spectro::Spectro(vector<complex<double> > iq_samples, double carrier_freq,
             double sampling_freq, unsigned int fft_size, vector<double> window) {

        iq_samples_ = iq_samples;
        carrier_freq_ = carrier_freq;
        sampling_freq_ = sampling_freq;
        fft_size_ = fft_size;
        //overlap_ = overlap;
        window_ = window;
        //average_ffts_ = average_ffts;
        /*in_ = in;
        out_ = out;
        plan_ = plan;
        empty_vector_ = empty_vector;
        fft_data_ = fft_data;*/
	gp << "set terminal x11\n";
}
Spectro::~Spectro() {
        fftw_destroy_plan(plan_);
        fftw_free(in_);
        fftw_free(out_);
}

// beginning of each FFT
/*unsigned int Spectro::start(int index, unsigned int fft_size, double overlap) {
        return fft_size_*overlap_*index;
}
*/
// end of each FFT
/*unsigned int Spectro::stop(int index, unsigned int fft_size, double overlap) {
        return fft_size_*overlap_*index + fft_size_ -1;//start(index, fft_size_, overlap_) + fft_size_ - 1;
}
*/
//spectrogram function
void Spectro::fft_generate() { //unsigned int average_ffts) {

/*vector<complex<float> > iq_samples, double carrier_freq,
                  double sampling_freq, unsigned int fft_size, double overlap,
                  vector<complex<float> > window */

//overlap_ = 1-overlap_;
//unsigned int N = iq_samples_.size();
//int index = 0;

//cout<<"Generating FFTs ... ";
/*
vector<complex<double> > s;
vector<complex<double> > s2;
s2.resize(fft_size_,0);
s.resize(fft_size_,0);
*/
// implement fft in c++
//mags_.resize(fft_size_,0);
//fft_data_.resize(fft_size_,0);

//out_ = (fftw_complex*) &empty_vector_.front();

//plan_ = fftw_plan_dft_1d(fft_size_, in_, out_, FFTW_FORWARD, FFTW_ESTIMATE);
	
	std::cout<<"fft_generate\n";

in_ = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*fft_size_);
out_ = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*fft_size_);
plan_ = fftw_plan_dft_1d(fft_size_, in_, out_, FFTW_FORWARD, FFTW_ESTIMATE);

fft_data_.clear();

for (unsigned int i = 0; i < fft_size_; ++i) {
        in_[i][0] = iq_samples_.at(i).real()*window_.at(i);
        in_[i][1] = iq_samples_.at(i).imag()*window_.at(i);
}
std::cout<<"Windowing\n";
fftw_execute(plan_);

unsigned int fft_half = fft_size_/2;
if (fft_size_ % 2 == 1) {
        fft_half++;
}

for (unsigned int i = fft_half; i < fft_size_; ++i) {
        fft_data_.push_back(sqrt(pow(out_[i][0],2) + pow(out_[i][1],2)));
}
std::cout<<"fftshift1\n";

for (unsigned int i = 0; i < fft_half; ++i) {
        fft_data_.push_back(sqrt(pow(out_[i][0],2) + pow(out_[i][1],2)));
}
std::cout<<"fftshift2\n";

iq_samples_.clear();

//cout<<"Done"<<endl;
}

void Spectro::fft_plot() {
        std::cout<<"fft_plot\n";
	vector<pair<double,double> > xy_pts_A;
        for (unsigned int i = 0; i < fft_size_; ++i) {
                xy_pts_A.push_back(make_pair(sampling_freq_/fft_size_*i + carrier_freq_ - sampling_freq_/2,
                20*log10(fft_data_.at(i)/1000.0)));
        }
	std::cout<<"Magnitudes\n";

        gp << "plot '-' binary" << gp.binFmt1d(xy_pts_A, "record") << "with lines notitle\n";
        gp.sendBinary1d(xy_pts_A);
        gp.flush();
}

