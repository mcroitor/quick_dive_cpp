#include "mymath.h"
#include "catch_amalgamated.hpp"

TEST_CASE("min") {
    REQUIRE(my::min(5, -10) == -10);
    REQUIRE(my::min(-10, 5) == -10);
    REQUIRE(my::min(5, 5) == 5);
}

TEST_CASE("mod") {
    REQUIRE(my::mod(5) == 5);
    REQUIRE(my::mod(-5) == 5);
    REQUIRE(my::mod(0) == 0);
}
