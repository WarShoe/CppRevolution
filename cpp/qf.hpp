#pragma once
#include <string>

namespace qf {

enum class Type {
    Call           = 1<<1,
    Put            = 1<<2,
    Straddle       = 1<<3,
    Forward        = 1<<4,
};

// returns: call, put
std::pair<double,double> Black76 (
    double stock,
    double strike,
    double sigma,
    double time,
    double discount
);

double Black76 (
    double stock,
    double strike,
    double sigma,
    double time,
    double discount,
    Type t
);

double Black76_ivol (
    double price,
    Type t,
    double stock,
    double strike,
    double time,
    double discount,
    double vol_start = 0.1,
    double vol_lo = 0,
    double vol_hi = 1,
    double price_tolerance=1e-9
);

std::pair<double,double> Bachelier (
    double stock,
    double strike,
    double sigma,
    double time,
    double discount
);

double Bachelier (
    double stock,
    double strike,
    double sigma,
    double time,
    double discount,
    Type t
);

double Bachelier_ivol (
    double price,
    Type t,
    double stock,
    double strike,
    double time,
    double discount,
    double vol_start = 0.1,
    double vol_lo = 0,
    double vol_hi = 1,
    double price_tolerance=1e-9
);

}
