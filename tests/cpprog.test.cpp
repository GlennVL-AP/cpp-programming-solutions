#include <catch.hpp>

import cpprog;

TEST_CASE("test cpprog::expect", "[cpprog][expect]")
{
    SECTION("expect does not throw when predicate is true")
    {
        REQUIRE_NOTHROW(cpprog::expect([] { return true; }, "should not throw"));
    }

    SECTION("expect throws when predicate is false")
    {
        REQUIRE_THROWS_MATCHES(
            cpprog::expect([] { return false; }, "should throw"),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("should throw"))
        );
    }
}

TEST_CASE("test cpprog::narrow_cast", "[cpprog][narrow_cast]")
{
    SECTION("narrowing does not throw if no information is lost")
    {
        REQUIRE_NOTHROW(cpprog::narrow_cast<int>(3.0));
        REQUIRE_NOTHROW(cpprog::narrow_cast<char>(127));
    }

    SECTION("narowing throws when information is lost")
    {
        REQUIRE_THROWS_AS(cpprog::narrow_cast<int>(3.14), cpprog::NarrowingError);
        REQUIRE_THROWS_AS(cpprog::narrow_cast<char>(1'024), cpprog::NarrowingError);
    }
}
