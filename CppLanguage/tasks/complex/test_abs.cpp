#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "abs.hpp"
#include "complex.hpp"

TEST_CASE("Test abs") {
  SECTION("Test trivial types") {
    REQUIRE(Abs(2.0) == 2.0);
    REQUIRE(Abs(-2.0) == 2.0);
    REQUIRE(Abs<double>(2.0) == 2.0);  // Check that abs is a template function.
  }
  SECTION("Check template specialization"){
    REQUIRE(Abs(Complex(3.0, 4.0)) == 5.0);
  }
}