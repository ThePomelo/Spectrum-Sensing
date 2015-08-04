#include <boost/lexical_cast.hpp>
#include "real_time_plotting.h"
#include "gnuplot-iostream.h"

RealTimePlotting::RealTimePlotting(std::unordered_map<std::string, std::string> *fft_map,
                                std::unordered_map<std::string, std::string> *radio_map,
                                log4cxx::LoggerPtr logger, Radio *radio) {
    all_set_ = false;
    logger_ = logger;
    radio_ = radio;
    ts_parameter_map_ = fft_map;
    radio_parameter_map_ = radio_map;

    carrier_freq_ = boost::lexical_cast<double>(radio_parameter_map_->at("uhd_rx_freq"));
    sampling_freq_ = boost::lexical_cast<double>(radio_parameter_map_->at("uhd_rx_rate"));
    fft_size_ = sampling_freq_/25;
    //overlap_ = 0;
    window_ = std::vector<double> (fft_size_,1);
    all_set_ = true;
}

RealTimePlotting::~RealTimePlotting() {

}

std::string RealTimePlotting::Set(std::string param_name, std::string param_value) {
    // Check if we care about this param
    if (ts_parameter_map_->count(param_name)) {
        ts_parameter_map_->at(param_name) = param_value;
        if (param_name == "recv_numbins") {
            return boost::str(boost::format("recv_numbins %s") % ts_parameter_map_->at("recv_numbins"));
        }
        else {
            return ("Error: Receiver unable to handle parameter: " + param_name);
        }
    }
    else {
        return ("Error: Unknown receiver parameter: " + param_name);
    }
    return("OK");
}

std::string RealTimePlotting::Get(std::string param_name) {
  // Check if we care about this param
  std::string temp;
  // Make sure all consumers also process it
  temp = ts_parameter_map_->at(param_name);
  return(temp);
}

void RealTimePlotting::Proc(std::vector<std::complex<float> > *recv_buffer) {
    std::cout<<"Proc!\n";
    if (all_set_) {
        auto I = recv_buffer->begin();
        std::cout<<"Sample buffer\n";
	while (iq_samples_.size() < fft_size_ and I != recv_buffer->end()) {
            iq_samples_.push_back(*I);
            ++I;
        }
        if (iq_samples_.size() == fft_size_) {
            fft_generate();
            fft_plot();
        }
    }
}
