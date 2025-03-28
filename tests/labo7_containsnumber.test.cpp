#include <catch.hpp>

import containsnumber;

TEST_CASE("test contains_number function", "[contains_number][labo_7]")
{
    std::vector const numbers{1, 2, 1, 3, 1, 4, 1, 5};

    SECTION("contains_number returns true if vector contains the number")
    {
        REQUIRE(contains_number(numbers, 1));
        REQUIRE(contains_number(numbers, 2));
        REQUIRE(contains_number(numbers, 3));
        REQUIRE(contains_number(numbers, 4));
        REQUIRE(contains_number(numbers, 5));
    }

    SECTION("contains_number returns false if vector does not contain the number")
    {
        REQUIRE_FALSE(contains_number(numbers, 0));
        REQUIRE_FALSE(contains_number(numbers, 6));
    }
}
