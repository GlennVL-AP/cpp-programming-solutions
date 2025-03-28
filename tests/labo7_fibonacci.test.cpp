#include <catch.hpp>

import cpprog;
import fibonacci;

TEST_CASE("test fibonacci implementation with cache", "[fibonacci][labo_7]")
{
    SECTION("cannot calculate negative fibonacci number")
    {
        REQUIRE_THROWS_MATCHES(
            fib_loop(-1),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("Number must be positive!"))
        );
    }

    SECTION("zero-th fibonnaci number is zero")
    {
        REQUIRE(fib_loop(0) == 0);
    }

    SECTION("first and second fibonacci numbers are one")
    {
        REQUIRE(fib_loop(1) == 1);
        REQUIRE(fib_loop(2) == 1);
    }

    SECTION("n-th fibonacci number is sum of fib(n-1) and fib(n-2)")
    {
        REQUIRE(fib_loop(3) == 2);
        REQUIRE(fib_loop(4) == 3);
        REQUIRE(fib_loop(5) == 5);
        REQUIRE(fib_loop(6) == 8);
        REQUIRE(fib_loop(7) == 13);
        REQUIRE(fib_loop(8) == 21);
        REQUIRE(fib_loop(9) == 34);
    }

    SECTION("largest fibonacci number that fits in a 64 bit integer")
    {
        REQUIRE(fib_loop(92) == 7'540'113'804'746'346'429);
    }
}

TEST_CASE("test recursive fibonacci implementation with cache", "[fibonacci][labo_7]")
{
    SECTION("cannot calculate negative fibonacci number")
    {
        REQUIRE_THROWS_MATCHES(
            fib_recursive(-1),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("Number must be positive!"))
        );
    }

    SECTION("zero-th fibonnaci number is zero")
    {
        REQUIRE(fib_recursive(0) == 0);
    }

    SECTION("first and second fibonacci numbers are one")
    {
        REQUIRE(fib_recursive(1) == 1);
        REQUIRE(fib_recursive(2) == 1);
    }

    SECTION("n-th fibonacci number is sum of fib(n-1) and fib(n-2)")
    {
        REQUIRE(fib_recursive(3) == 2);
        REQUIRE(fib_recursive(4) == 3);
        REQUIRE(fib_recursive(5) == 5);
        REQUIRE(fib_recursive(6) == 8);
        REQUIRE(fib_recursive(7) == 13);
        REQUIRE(fib_recursive(8) == 21);
        REQUIRE(fib_recursive(9) == 34);
    }

    SECTION("largest fibonacci number that fits in a 64 bit integer")
    {
        REQUIRE(fib_recursive(92) == 7'540'113'804'746'346'429);
    }
}

TEST_CASE("benchmark fibonacci", "[!benchmark][fibonacci][labo_7]")
{
    BENCHMARK("fibonacci implementation with loop and cache")
    {
        return fib_loop(92);
    };

    BENCHMARK("recursive fibonacci implementation with cache")
    {
        return fib_recursive(92);
    };
}
