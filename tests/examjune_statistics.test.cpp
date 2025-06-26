#include <catch.hpp>

import cpprog;
import statistics;

TEST_CASE("Statistics works correctly", "[statistics]")
{
    Statistics stats{};

    SECTION("empty list")
    {
        REQUIRE_THROWS_MATCHES(
            stats.sum(),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("list must not be empty"))
        );

        REQUIRE_THROWS_MATCHES(
            stats.average(),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("list must not be empty"))
        );

        REQUIRE_THROWS_MATCHES(
            stats.max(),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("list must not be empty"))
        );
    }

    SECTION("with elements")
    {
        stats.add(5);
        stats.add(3);
        stats.add(4);

        REQUIRE(stats.sum() == 12);
        REQUIRE(stats.average() == 4.0);
        REQUIRE(stats.max() == 5);
    }
}
