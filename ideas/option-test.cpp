#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <fmt/core.h>

#include "qf.hpp"

#include "option.hpp"

// constexpr double
//     eps_default = 1e-10;

using namespace qf;

TEST_CASE("option") {
    using Time   = double;
    using Equity = double;
    
    Time now {0}, Y{1};

    Option<Equity> eo;
    eo.underlying = Equity {10};
    eo.expiry = 2*Y;

    // auto approx = [] (double v) {return doctest::Approx(v).epsilon(eps_default);};
    // REQUIRE( math::cndf(0) == approx(0.5) );
    // for( auto x: {0.,0.5,1.,2.,3.,10.})
    //     REQUIRE( math::cndf(-x)+math::cndf(x) == approx(1) );


    REQUIRE( pv(now,eo) );
}
