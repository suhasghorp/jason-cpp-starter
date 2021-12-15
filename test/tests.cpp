#include <catch2/catch.hpp>

#include "../src/lib/cpplib.h"
#include <Eigen/Core>
#include <boost/math/quadrature/trapezoidal.hpp>
#if (__GNUC__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wsign-conversion"
  #pragma GCC diagnostic ignored "-Wconversion"
  #pragma GCC diagnostic ignored "-Wold-style-cast"
  #pragma GCC diagnostic ignored "-Wuseless-cast"
  #include <EigenRand/EigenRand>
  #pragma GCC diagnostic pop
#elif (__clang__)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wsign-conversion"
  #pragma clang diagnostic ignored "-Wconversion"
  #pragma clang diagnostic ignored "-Wold-style-cast"
  #pragma clang diagnostic ignored "-Wshadow"
  #include <EigenRand/EigenRand>
  #pragma clang diagnostic pop

#endif

unsigned int Factorial(unsigned int number)// NOLINT(misc-no-recursion)
{
  return number <= 1 ? number : Factorial(number - 1) * number;
}

TEST_CASE("Factorials are computed", "[factorial]")
{
  REQUIRE(Factorial(1) == 1);
  REQUIRE(Factorial(2) == 2);
  REQUIRE(Factorial(3) == 6);
  REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("FindMax", "[cpplib]") {
  CPPLib cpplib;

  SECTION("Should find max of consecutive numbers") {
    std::vector<int> inputs = {1, 2, 3, 4};
    REQUIRE(cpplib.FindMax(inputs) == 4);
  }

  SECTION("Should find max of non consecutive numbers") {
    std::vector<int> inputs = {1, 7, 3, 4};
    REQUIRE(cpplib.FindMax(inputs) == 7);
  }

  SECTION("Should find max with negative numbers") {
    std::vector<int> inputs = {-1, -7, -3, -4};
    REQUIRE(cpplib.FindMax(inputs) == -1);
  }

  SECTION("Should find max of all equal values") {
    std::vector<int> inputs = {-1, -1, -1, -1};
    REQUIRE(cpplib.FindMax(inputs) == -1);
  }

  SECTION("Should find return min for empty vector") {
    std::vector<int> inputs = {};
    REQUIRE(cpplib.FindMax(inputs) == std::numeric_limits<int>::min());
  }

  SECTION("Should find return min for empty vector") {
    std::vector<int> inputs = {1000};
    REQUIRE(cpplib.FindMax(inputs) == 1000);
  }
}
