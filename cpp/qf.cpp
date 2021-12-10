#include <cmath>
#include <fmt/core.h>

#include "qf.hpp"
#include "math.hpp"

namespace qf {

std::pair<double,double> Black76 (
    double stock,
    double strike,
    double sigma,
    double time,
    double discount
){
    auto
        sigma_sqrt_time = sigma * std::sqrt(time),
        forward         = stock/discount,
        d               = std::log(forward/strike) / sigma_sqrt_time,
        d1              = d + sigma_sqrt_time/2,
        d2              = d - sigma_sqrt_time/2,
        cndf_d1p        = math::cndf(d1),
        cndf_d2p        = math::cndf(d2),
        cndf_d1n        = 1-cndf_d1p,
        cndf_d2n        = 1-cndf_d2p,
        price_call      = cndf_d1p * stock             - cndf_d2p * strike * discount,
        price_put       = cndf_d2n * strike * discount - cndf_d1n * stock;
    return {price_call, price_put};
}

double Black76 (
    double stock,
    double strike,
    double sigma,
    double time,
    double discount,
    Type t
){
    auto r = Black76(stock,strike,sigma,time,discount);
    switch(t){
        case Type::Call: return r.first;
        case Type::Put : return r.second;
        default: throw std::invalid_argument(__PRETTY_FUNCTION__);
    }
}

double Black76_ivol (
    double price,
    Type t,
    double stock,
    double strike,
    double time,
    double discount,
    double vol_start,
    double vol_lo,
    double vol_hi,
    double price_tolerance
){
    return math::root_finder(
        [&] (double sigma) {
            return price - Black76(stock,strike,sigma,time,discount,t);
        },
        vol_start,
        vol_lo,
        vol_hi,
        1e-3, // step
        100, // iters max
        1e-100, // sigma tolerance
        price_tolerance
    );
}

std::pair<double,double> Bachelier (
    double stock,
    double strike,
    double sigma,
    double time,
    double discount
){
    auto
        sigma_sqrt_time = sigma * std::sqrt(time),
        forward         = stock/discount,
        dp              = (forward-strike) / sigma_sqrt_time,
        ndf_dp          = math::ndf(dp),
        cndf_dp         = math::cndf(dp),
        cndf_dm         = 1-math::cndf(cndf_dp),
        price_call      = discount*( (forward-strike)*cndf_dp + sigma_sqrt_time*ndf_dp ),
        price_put       = discount*( (strike-forward)*cndf_dm + sigma_sqrt_time*ndf_dp );
    return {price_call, price_put};
}

double Bachelier (
    double stock,
    double strike,
    double sigma,
    double time,
    double discount,
    Type t
){
    auto r = Bachelier(stock,strike,sigma,time,discount);
    switch(t){
        case Type::Call: return r.first;
        case Type::Put : return r.second;
        default: throw std::invalid_argument(__PRETTY_FUNCTION__);
    }
}

        // public static double Bachelier(double discountFactor, double forward, double sigma, bool isCallNotPut, double strike, double tau)
        // {
        //     //double accumulatedVol = sigma * Math.Sqrt(tau);
        //     double d = (forward - strike) / accumulatedVol;
        //     double undiscountedPrice = isCallNotPut
        //         ? accumulatedVol * SpecialFunctions.ndf(d) + (forward - strike) * SpecialFunctions.cndf(d)
        //         : accumulatedVol * SpecialFunctions.ndf(d) + (strike - forward) * SpecialFunctions.cndf(-d);

        //     return discountFactor*undiscountedPrice;
        // }

double Bachelier_ivol (
    double price,
    Type t,
    double stock,
    double strike,
    double time,
    double discount,
    double vol_start,
    double vol_lo,
    double vol_hi,
    double price_tolerance
){
    return math::root_finder(
        [&] (double sigma) {
            return price - Bachelier(stock,strike,sigma,time,discount,t);
        },
        vol_start,
        vol_lo,
        vol_hi,
        1e-3, // step
        100, // iters max
        1e-100, // sigma tolerance
        price_tolerance
    );
}


}
