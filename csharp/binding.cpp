#include "qf.hpp"

extern "C" {

double Black76 (
    double discount,
    double forward,
    double sigma,
    bool   isCallNotPut,
    double strike,
    double tau
){
    return qf::Black76 (
        forward*discount,
        strike,
        sigma,
        tau,
        discount,
        isCallNotPut ? qf::Type::Call : qf::Type::Put
    );
}


double Bachelier (
    double discount,
    double forward,
    double sigma,
    bool   isCallNotPut,
    double strike,
    double tau
){
    return qf::Bachelier (
        forward*discount,
        strike,
        sigma,
        tau,
        discount,
        isCallNotPut ? qf::Type::Call : qf::Type::Put
    );
}

double Black76_ivol (
    double price,
    bool   isCallNotPut,
    double stock,
    double strike,
    double time,
    double discount,
    double vol_start,
    double vol_lo,
    double vol_hi,
    double price_tolerance
){
    return qf::Black76_ivol(
        price,
        isCallNotPut ? qf::Type::Call : qf::Type::Put,
        stock,
        strike,
        time,
        discount,
        vol_start,
        vol_lo,
        vol_hi,
        price_tolerance
    );
}

double Bachelier_ivol (
    double price,
    bool   isCallNotPut,
    double stock,
    double strike,
    double time,
    double discount,
    double vol_start,
    double vol_lo,
    double vol_hi,
    double price_tolerance
){
    return qf::Bachelier_ivol(
        price,
        isCallNotPut ? qf::Type::Call : qf::Type::Put,
        stock,
        strike,
        time,
        discount,
        vol_start,
        vol_lo,
        vol_hi,
        price_tolerance
    );
}

}
