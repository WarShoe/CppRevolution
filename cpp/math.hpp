#pragma once

#include <cmath>

namespace math {

inline
double ndf (
    double x,
    double mean  = 0,
    double sigma = 1
){
    return 1/(std::sqrt(2*M_PI)*sigma) * std::exp( - std::pow((x-mean)/sigma,2) / 2 );
}

inline
double cndf (
    double x
){
    return 1-0.5*std::erfc(x/sqrt(2));
}

// 1D function root finder
template <typename F>
double
root_finder (
    F f,
    double start, // start, must be low<=x<=start
    double low, // low limit, must be low<high
    double high, // high limit, must be low<high
    double step=0, // use it if positve, otherwise step=(high-low)/100,
    int iters_max=100, // stop condition: number of iterations
    double xstep_tolerance=1e-100, // stop condition: 'x' did not change much
    double func_tolerance=1e-100, // stop condition: function is close to 0
    double deriv_tolerance=1e-100 // stop condition: function derivative is close to 0
){
    if(not(step>0))
        step = (high-low)/100;

    double x = start;
    for(int iter=0; true; iter++){
        double
            fx = f(x),
            dx = step,
            xstepped = x+dx,
            fx_stepped = NAN;
        if(std::isnan(fx))
            throw std::runtime_error(fmt::format("{} cannot compute f({})",__PRETTY_FUNCTION__,x));

        if(     iter>=iters_max
            or  std::fabs(fx)<=func_tolerance
        )
            return x;

        if(xstepped <= high){
            fx_stepped = f(xstepped);
        } else {
            dx = -step;
            xstepped = x+dx;
            if(xstepped >= low)
                fx_stepped = f(xstepped);
        }
        if(std::isnan(fx_stepped))
            throw std::runtime_error(fmt::format("{} cannot compute derivative at x={}",__PRETTY_FUNCTION__,x));
        double
            derivative = (fx_stepped-fx)/dx,
            x_next = x - fx/derivative;
        
        if(std::isnan(x))
            throw std::runtime_error(fmt::format("{} failed!",__PRETTY_FUNCTION__));
        
        if(x_next<low ) x_next = low;
        if(x_next>high) x_next = high;
        
        if(     std::fabs(derivative)<=deriv_tolerance
            or  std::fabs(x-x_next)<=xstep_tolerance
        ) return x_next;

        // fmt::print("x={} x'={} dx={} fx={} fx_stepped={} deriv={}\n",x,x_next,dx,fx,fx_stepped,derivative);
        x = x_next;
    }

    return x;
}

}
