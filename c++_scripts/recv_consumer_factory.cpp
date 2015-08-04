#include "recv_consumer_factory.h"
//#include 'CRecvFft.h"
#include "fft_movavg_oml.h"
#include "fft_sigpower_oml.h"
#include "fft_movavg_udp.h"
#include "fft_pow_udp.h"
#include "time_samples_to_file.h"
#include "real_time_plotting.h"

std::vector<std::vector<std::string> > RecvConsumerFactory::GetConsumerList() {
  std::vector<std::vector<std::string> > consumer_list;
  std::vector<std::string> cons;
  cons.push_back(FFTMovingAvgOml::Name());
  cons.push_back("RX: Send FFT average with a window of length 'recv_avgwinlen' to OML");
  consumer_list.push_back(cons);
  cons.clear();
  cons.push_back(FFTSigPowerOml::Name());
  cons.push_back("RX: Send signal power in dBm to OML");
  consumer_list.push_back(cons);
  cons.clear();
  cons.push_back(FFTMovingAvgUdp::Name());
  cons.push_back("RX: Send FFT average with a window of length 'recv_avgwinlen' to a UDP socket specified with 'recv_udp_uri' and 'recv_udp_port'");
  consumer_list.push_back(cons);
  cons.clear();
  cons.push_back(FFTPowUdp::Name());
  cons.push_back("RX: Send signal power in dBm to UDP");
  consumer_list.push_back(cons);
  cons.clear();
  cons.push_back(TimeSamplesToFile::Name());
  cons.push_back("RX: Store time samples to a binary file with name specified by 'recv_output_filename'");
  consumer_list.push_back(cons);
  cons.clear();
  cons.push_back(RealTimePlotting::Name());
  cons.push_back("RX: Plot FFTs in real time");
  consumer_list.push_back(cons);
  cons.clear();
  return consumer_list;
}

RecvConsumer* RecvConsumerFactory::NewRecvConsumer(const std::string name,
               std::unordered_map<std::string, std::string> *param_map,
               std::unordered_map<std::string, std::string> *radio_map,
               log4cxx::LoggerPtr logger, Radio *radio) {
//  if(name == "fft1") return new CRecvFft;
//  if(name == "fft2") return new CRecvOML;
  if (name == FFTMovingAvgOml::Name()) {
    return new FFTMovingAvgOml(param_map, radio_map, logger, radio);
  } else if (name == FFTSigPowerOml::Name()) {
    return new FFTSigPowerOml(param_map, radio_map, logger, radio);
  } else if (name == FFTMovingAvgUdp::Name()) {
    return new FFTMovingAvgUdp(param_map, radio_map, logger, radio);
  } else if (name == FFTPowUdp::Name()) {
    return new FFTPowUdp(param_map, radio_map, logger, radio);
  } else if (name == TimeSamplesToFile::Name()) {
    return new TimeSamplesToFile(param_map, radio_map, logger, radio);
  } else if (name == RealTimePlotting::Name()) {
    return new RealTimePlotting(param_map, radio_map, logger, radio);
  }
  return NULL;
}

void RecvConsumerFactory::DeleteRecvConsumer(const std::string name, RecvConsumer *consumer) {
  if (name == FFTMovingAvgOml::Name()) {
    delete (FFTMovingAvgOml *) consumer;
  } else if (name == FFTSigPowerOml::Name()) {
    delete (FFTSigPowerOml *) consumer;
  } else if (name == FFTMovingAvgUdp::Name()) {
    delete (FFTMovingAvgUdp *) consumer;
  } else if (name == FFTPowUdp::Name()) {
    delete (FFTPowUdp *) consumer;
  } else if (name == TimeSamplesToFile::Name()) {
    delete (TimeSamplesToFile *) consumer;
  } else if (name == RealTimePlotting::Name()) {
    delete (RealTimePlotting *) consumer;
  }
}
