#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "complex.hpp"

TEST_CASE("Complex initialization") {
  SECTION("Default constructor") {
    Complex complex;
    REQUIRE(complex.GetRe() == 0.0);
    REQUIRE(complex.GetIm() == 0.0);
  }
  SECTION("Copy constructor") {
    Complex complex(1.0, 1.0);
    Complex copy = complex;
    REQUIRE(complex.GetRe() == copy.GetRe());
    REQUIRE(complex.GetIm() == copy.GetIm());
  }
  SECTION("From real constructor") {
    Complex complex = 1.0;
    REQUIRE(complex.GetRe() == 1.0);
    REQUIRE(complex.GetIm() == 0.0);
  }
}

TEST_CASE("Non-mutated methods marked const") {
  const Complex complex(1.0, 1.0);
  REQUIRE(complex.GetRe() == 1.0);
  REQUIRE(complex.GetIm() == 1.0);
}

TEST_CASE("Check unary arithmetic operators") {
  Complex complex(1.0, 1.0);
  SECTION("Test unary plus") {
    Complex plus = +complex;
    REQUIRE(complex.GetRe() == plus.GetRe());
    REQUIRE(complex.GetIm() == plus.GetIm());
  }

  SECTION("Test unary minus") {
    Complex minus = -complex;
    REQUIRE(complex.GetRe() == -minus.GetRe());
    REQUIRE(complex.GetIm() == -minus.GetIm());
  }
}

TEST_CASE("Test comparison") {
  Complex complex_1_1(1, 1);
  Complex complex_0_0(0, 0);
  Complex other_0_0(0, 0);

  REQUIRE(complex_0_0 != complex_1_1);
  REQUIRE(complex_0_0 == other_0_0);
}

TEST_CASE("Test assignment operators") {
  Complex complex(1.0, 1.0);
  SECTION("+=") {
    complex += Complex(1.0, 1.0);
    REQUIRE(complex == Complex(2.0, 2.0));
  }
  SECTION("-=") {
    complex -= Complex(1.0, 1.0);
    REQUIRE(complex == Complex(0.0, 0.0));
  }
  SECTION("*=") {
    complex *= Complex(1.0, 1.0);
    REQUIRE(complex == Complex(0.0, 2.0));
  }
}

TEST_CASE("Test binary arithmetic operators") {
  Complex lhs(1.0, 1.0);
  Complex rhs(1.0, 1.0);
  SECTION("+") {
    REQUIRE(Complex(2.0, 2.0) == lhs + rhs);
  }
  SECTION("-") {
    REQUIRE(Complex(0.0, 0.0) == lhs - rhs);
  }
  SECTION("*") {
    REQUIRE(Complex(0.0, 2.0) == lhs * rhs);
  }
}
