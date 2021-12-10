namespace computations {

template <typename Underlying,typename Time=double>
class Option {
public:
    Time       expiry;
    Underlying underlying;
};

template <typename Underlying,typename Time=double>
double pv_call (
    Time now,
    const Option<Underlying> &option
){
    return NAN;
}

}

int main () {

    using Equity = double;
    auto my_option = Option<Equity>();

    return 0;
}
