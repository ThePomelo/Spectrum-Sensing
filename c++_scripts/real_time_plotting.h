#ifndef REAL_TIME_PLOTTING_H__
#define REAL_TIME_PLOTTING_H__

#include <complex>
#include <log4cxx/logger.h>
#include "recv.h"
#include "recv_consumer.h"
#include "radio.h"
#include "spectro.h"
#include "gnuplot-iostream.h"

class Recv;

class Spectro;

class RealTimePlotting : public RecvConsumer, public Spectro {
    private:
        std::unordered_map<std::string, std::string> *ts_parameter_map_;
        std::unordered_map<std::string, std::string> *radio_parameter_map_;

        bool all_set_;
        Recv *receiver_;
        Radio *radio_;
        log4cxx::LoggerPtr logger_;
    public:
        RealTimePlotting(std::unordered_map<std::string, std::string> *fft_map,
            std::unordered_map<std::string, std::string> *radio_map,
            log4cxx::LoggerPtr logger, Radio *radio);
        ~RealTimePlotting();
        void Proc(std::vector<std::complex<float> > *recv_buffer);
        std::string Set(std::string param_name, std::string param_value);
        std::string Get(std::string param_name);
        static std::string Name() {return "realtimeplotting";}
};

#endif
