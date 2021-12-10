#pragma once

namespace qf {

template <typename Underlying,typename Time=double>
class Option {
public:
    Time       expiry;
    Underlying underlying;
};

template <typename Underlying,typename Time=double>
double pv (
    Time now,
    const Option<Underlying> &option
){
    return NAN;
}

}
