#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "array.hpp"
#include "array.hpp"  // Check Guards or pragma.

TEST_CASE("Array tests") {
  Array<int, 4> arr{1, 2, 3, 4};  // Constructor from init-list

  SECTION("Check object after instantiation") {
    static_assert(sizeof(arr) == sizeof(int) * 4);  // Compile-time check.
    REQUIRE(arr.Size() == 4);
    REQUIRE_FALSE(arr.Empty());
  }

  SECTION("Check operator[]") {
    REQUIRE(arr[0] == 1);
    arr[1] = 0;
    REQUIRE(arr[1] == 0);
  }

  SECTION("Check data access methods methods") {
    REQUIRE(arr.Front() == 1);
    REQUIRE(arr.Back() == 4);
    REQUIRE(arr.Data() == &arr[0]);
  }

  SECTION("Check that Front, Back methods returns reference") {
    arr.Front() = -1;
    REQUIRE(arr.Front() == -1);
    arr.Back() = -1;
    REQUIRE(arr.Back() == -1);
  }

  SECTION("Check Swap") {
    Array<int, 4> other{0, 0, 0, 0};
    other.Swap(arr);
    REQUIRE(other[0] == 1);
    REQUIRE(other[1] == 2);
    REQUIRE(other[2] == 3);
    REQUIRE(other[3] == 4);

    REQUIRE(arr[0] == 0);
    REQUIRE(arr[1] == 0);
    REQUIRE(arr[2] == 0);
    REQUIRE(arr[3] == 0);
  }

  SECTION("Const methods") {  // Assertions are the same, but code won't compile in case of absence const qualifiers
    const Array<int, 4>& const_ref = arr;
    REQUIRE(const_ref[0] == 1);
    REQUIRE(const_ref.Front() == 1);
    REQUIRE(const_ref.Back() == 4);
    REQUIRE(const_ref.Data() == &arr[0]);
  }
}
