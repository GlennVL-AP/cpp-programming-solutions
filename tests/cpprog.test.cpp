#include <catch.hpp>

import cpprog;
import std;

TEST_CASE("test cpprog::version", "[cpprog][version]")
{
    SECTION("get version")
    {
        auto const expected = cpprog::version::as_string();
        auto const actual =
            std::format("{}.{}.{}", cpprog::version::get().major, cpprog::version::get().minor, cpprog::version::get().patch);

        REQUIRE(actual == expected);
    }

    SECTION("compare versions")
    {
        using cpprog::version::VersionInfo;

        STATIC_REQUIRE(VersionInfo{1, 2, 3} == VersionInfo{1, 2, 3});
        STATIC_REQUIRE(VersionInfo{1, 2, 3} != VersionInfo{3, 2, 1});
        STATIC_REQUIRE(VersionInfo{1, 2, 3} < VersionInfo{2, 2, 3});
        STATIC_REQUIRE(VersionInfo{1, 2, 3} < VersionInfo{1, 3, 3});
        STATIC_REQUIRE(VersionInfo{1, 2, 3} < VersionInfo{1, 2, 4});
    }
}

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
