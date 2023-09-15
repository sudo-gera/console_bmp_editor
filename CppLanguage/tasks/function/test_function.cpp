#include <functional>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <type_traits>

#include "function.hpp"

template <typename T>
struct ClassWithMethod {
  template <typename... Args>
  T Method(Args&&... args) {
    if constexpr (std::is_default_constructible_v<T>) {
      return T{};
    } else {
      return T(std::forward(args)...);
    }
  }
};

template <typename T>
struct TestFunctor {
  template <typename... Args>
  T operator()(Args&&... args) {
    if constexpr (std::is_default_constructible_v<T>) {
      return T{};
    } else {
      return T(std::forward(args)...);
    }
  }
};

template <typename T, typename... Args>
T TestFunction(Args&&... args) {
  if constexpr (std::is_default_constructible_v<T>) {
    return T{};
  } else {
    return T(std::forward(args)...);
  }
}

TEST_CASE("Constructor") {  // Just check compilation.
  SECTION("Default") {
    Function<int()> f;
  }

  SECTION("Functor") {
    Function<int()> f = TestFunctor<int>();
  }
  SECTION("Function") {
    Function<int()> f = TestFunction<int>;
  }
  SECTION("Lambda") {
    Function<int()> f = []() -> int {
      return 1;
    };
  }
}

TEST_CASE("Assignment") {
  Function<int()> f;
  SECTION("Functor") {
    Function<int()> f = TestFunctor<int>();
  }
  SECTION("Function") {
    Function<int()> f = TestFunction<int>;
    f();
  }
  SECTION("Lambda") {
    Function<int()> f = []() -> int {
      return 1;
    };
    f();
  }
  SECTION("Other instance of Function") {
    SECTION("Copy") {
      Function<int()> functor = TestFunctor<int>();
      Function<int()> function = TestFunction<int>;
      Function<int()> lambda = []() -> int {
        return 1;
      };
      f = functor;
      f = function;
      f = lambda;
    }

    SECTION("Move") {
      Function<int()> functor = TestFunctor<int>();
      Function<int()> function = TestFunction<int>;
      Function<int()> lambda = []() -> int {
        return 1;
      };
      f = std::move(functor);
      f = std::move(function);
      f = std::move(lambda);
    }
  }
}

TEST_CASE("Empty") {
  Function<int()> f;
  REQUIRE_THROWS_AS(f(), std::bad_function_call);
}

TEMPLATE_TEST_CASE("Templates", "[Function][template]", int, std::string, (std::pair<int, double>),
                   (std::shared_ptr<int>), (std::tuple<int, float>), (std::vector<int>)) {
  Function<TestType()> function = TestFunction<TestType>;
  Function<TestType()> functor = TestFunctor<TestType>();
}

TEST_CASE("Same result") {
  Function<int()> f1 = []() -> int {
    return 1;
  };
  REQUIRE(f1() == 1);

  Function<int()> f2 = []() -> int {
    return 2;
  };
  REQUIRE(f2() == 2);

  Function<std::string()> f3 = []() -> std::string {
    return "1";
  };
  REQUIRE(f3() == "1");
}
