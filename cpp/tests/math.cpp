#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <fmt/core.h>

#include "math.hpp"
#include "qf.hpp"

constexpr double
    eps_default = 1e-10;

TEST_CASE("cndf") {
    auto approx = [] (double v) {return doctest::Approx(v).epsilon(eps_default);};
    REQUIRE( math::cndf(0) == approx(0.5) );
    for( auto x: {0.,0.5,1.,2.,3.,10.})
        REQUIRE( math::cndf(-x)+math::cndf(x) == approx(1) );
}

// template <
//     typename Result,
//     typename Function,
//     typename ... Args
// >
// void test (Result expected,Function f, Args ... args) {
//     REQUIRE( f(args ...) == doctest::Approx(expected).epsilon(eps_default));
// }

TEST_CASE("root_finder_1") {
    auto x = math::root_finder(
        [] (double x) {return 1+2*x;},
        0,-10,10
    );
    REQUIRE( x == doctest::Approx(-0.5).epsilon(eps_default));
}

TEST_CASE("root_finder_2") {
    auto x = math::root_finder(
        [] (double x) {return 100-x*x;},
        0,-20,20
    );
    REQUIRE( x == doctest::Approx(10).epsilon(eps_default));
}

TEST_CASE("root_finder_3") {
    auto x = math::root_finder(
        [] (double x) {return 100-x*x;},
        0,-5,5
    );
    REQUIRE( x == doctest::Approx(5).epsilon(eps_default));
}
