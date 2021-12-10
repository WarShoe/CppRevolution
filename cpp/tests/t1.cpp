#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <fmt/core.h>

#include "math.hpp"
#include "qf.hpp"

constexpr double
    pc          = 1e-2,
    eps_default = 1e-10;

// template <typename F,typename R>
// void test (
//     F       f,
//     R       r,
//     double  stock,
//     double  strike,
//     double  sigma,
//     double  time,
//     double  discount
// ){
//     auto approx = [] (double v) {return doctest::Approx(v).epsilon(eps_default);};
//     auto [expected_call,expected_put] = r;
//     auto [call,put] = f(stock,strike,sigma,time,discount);
//     REQUIRE( call == approx(expected_call) );
//     REQUIRE( put  == approx(expected_put ) );
// }

void test_Black76 (
    std::pair<double,double>    expect_call_put,
    double                      stock,
    double                      strike,
    double                      sigma,
    double                      time,
    double                      discount,
    double                      eps = eps_default
){
    auto approx = [=] (double v) {return doctest::Approx(v).epsilon(eps);};
    auto [expected_call,expected_put] = expect_call_put;
    auto [call,put] = qf::Black76(stock,strike,sigma,time,discount);
    REQUIRE( call == approx(expected_call) );
    REQUIRE( put  == approx(expected_put ) );
}

TEST_CASE("Black76") {
    // Test with some finate numbers
    test_Black76(
        {44.77364219900744, 138.77364219900755},
        2006, 2100, 35*pc, 31/365., 1
    );
    // // If discount=1 and sigma is BIG, then (call-put) = (strike-spot)
    // for( auto [spot,strike]: {{10,10},{10,20}}){
    //     test_Black76(
    //         {spot,138.77364219900755},
    //         2006,2100,35*pc,31/365.,1
    //     );
    // }
}

void test_Bachelier (
    std::pair<double,double>    expect_call_put,
    double                      stock,
    double                      strike,
    double                      sigma,
    double                      time,
    double                      discount,
    double                      eps = eps_default
){
    auto approx = [=] (double v) {return doctest::Approx(v).epsilon(eps);};
    auto [expected_call,expected_put] = expect_call_put;
    auto [call,put] = qf::Bachelier(stock,strike,sigma,time,discount);
    REQUIRE( call == approx(expected_call) );
    REQUIRE( put  == approx(expected_put ) );
}

TEST_CASE("Bachelier") {
    // Test with some finate numbers
    test_Bachelier(
        {0.0126156626,0.0126156626},
        0, 0, 10*pc, 0.1, 1
    );
    test_Bachelier(
        {0.0126156626,0.0126156626},
        100000, 100000, 10*pc, 0.1, 1
    );
    test_Bachelier(
        {0.252896919,0.9125069627},
        10, 11, 50*pc, 10, 1
    );

    // test(
    //     qf::Bachelier,
    //     std::pair<double,double>{0.252896919,0.9125069627},
    //     10, 11, 50*pc, 10, 1
    // );
}

TEST_CASE("ImpliedVolatility_Black76"){
    double stock=10, strike=11, sigma=0.5, time=2, discount=1;
    auto [call,put] = qf::Black76(stock,strike,sigma,time,discount);
    // fmt::print("ivol: {} {}\n",call,put);
    double
        ivol_call = qf::Black76_ivol(call,qf::Type::Call,stock,strike,time,discount),
        ivol_put  = qf::Black76_ivol(put ,qf::Type::Put ,stock,strike,time,discount);
    REQUIRE( ivol_call == doctest::Approx(sigma).epsilon(eps_default) );
    REQUIRE( ivol_put  == doctest::Approx(sigma).epsilon(eps_default) );

    // fmt::print("ivol calculated: {} {}\n",ivol_call,ivol_put);
}

TEST_CASE("ImpliedVolatility_Bachelier"){
    const double
        eps     = 1e-8,
        stock   = 10,
        strike  = 11,
        sigma   = 0.5,
        time    = 2,
        discount=1;
    auto [call,put] = qf::Bachelier(stock,strike,sigma,time,discount);
    // fmt::print("ivol: {} {}\n",call,put);
    double
        ivol_call = qf::Bachelier_ivol(call,qf::Type::Call,stock,strike,time,discount),
        ivol_put  = qf::Bachelier_ivol(put ,qf::Type::Put ,stock,strike,time,discount);
    REQUIRE( ivol_call == doctest::Approx(sigma).epsilon(eps) );
    REQUIRE( ivol_put  == doctest::Approx(sigma).epsilon(eps) );

    // fmt::print("ivol calculated: {} {}\n",ivol_call,ivol_put);
}
