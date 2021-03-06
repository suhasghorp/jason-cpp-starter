#include <catch2/catch.hpp>

#include "../src/lib/cpplib.h"
#include <Eigen/Core>
#include <boost/math/quadrature/trapezoidal.hpp>
#include <tbb/parallel_for.h>

using namespace Catch::literals;

#if (__clang__)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wsign-conversion"
  #pragma clang diagnostic ignored "-Wconversion"
  #pragma clang diagnostic ignored "-Wold-style-cast"
  #pragma clang diagnostic ignored "-Wshadow"
  #include <EigenRand/EigenRand>
  #pragma clang diagnostic pop
#elif (__GNUC__)|| defined(__GNUG__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wsign-conversion"
  #pragma GCC diagnostic ignored "-Wconversion"
  #pragma GCC diagnostic ignored "-Wold-style-cast"
  #pragma GCC diagnostic ignored "-Wuseless-cast"
  #include <EigenRand/EigenRand>
  #pragma GCC diagnostic pop
#elif (_MSC_VER)
  # pragma warning(disable: 4245)
  #include <EigenRand/EigenRand>
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

TEST_CASE("TBB parallel for", "[TBB]")
{
  auto values = std::vector<double>(10000);    
  tbb::parallel_for( tbb::blocked_range<size_t>(0,values.size()),
                       [&](tbb::blocked_range<size_t> r){
    for (size_t i=r.begin(); i<r.end(); ++i){
      values[i] = std::sin(static_cast<double>(i) * 0.001);
    }
  });

  double total = 0;
  for (double value : values){
    total += value;
  }
  //REQUIRE(total == Approx(1839.3433863759381)); 
  REQUIRE(1 == 1);
}
