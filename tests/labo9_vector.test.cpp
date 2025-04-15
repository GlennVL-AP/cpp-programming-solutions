#include <catch.hpp>

import cpprog;
import std;
import vector3d;

TEST_CASE("test vector of doubles", "[labo_9][vector3d]")
{
    constexpr linalg::Vector3D test_vec_1{linalg::X{1.0}, linalg::Y{2.0}, linalg::Z{3.0}};
    constexpr linalg::Vector3D test_vec_2{linalg::X{3.0}, linalg::Y{1.0}, linalg::Z{2.0}};

    SECTION("access values using the index operator")
    {
        STATIC_REQUIRE(test_vec_1[0] == test_vec_1.x().get());
        STATIC_REQUIRE(test_vec_1[1] == test_vec_1.y().get());
        STATIC_REQUIRE(test_vec_1[2] == test_vec_1.z().get());
    }

    SECTION("attempt to access invalid index")
    {
        REQUIRE_THROWS_MATCHES(
            test_vec_1[3],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("index must be 0, 1, 2"))
        );
    }

    SECTION("compare vectors")
    {
        STATIC_REQUIRE(test_vec_1 == test_vec_1);
        STATIC_REQUIRE(test_vec_1 != test_vec_2);
        STATIC_REQUIRE_FALSE(test_vec_1 == test_vec_2);
        STATIC_REQUIRE_FALSE(test_vec_1 != test_vec_1);
    }

    SECTION("add vectors")
    {
        constexpr auto actual = test_vec_1 + test_vec_2;

        STATIC_REQUIRE(actual[0] == 4.0);
        STATIC_REQUIRE(actual[1] == 3.0);
        STATIC_REQUIRE(actual[2] == 5.0);
    }

    SECTION("subtract vectors")
    {
        constexpr auto actual = test_vec_1 - test_vec_2;

        STATIC_REQUIRE(actual[0] == -2.0);
        STATIC_REQUIRE(actual[1] == 1.0);
        STATIC_REQUIRE(actual[2] == 1.0);
    }

    SECTION("multiply by scalar")
    {
        constexpr auto actual = test_vec_1 * 2.0;

        STATIC_REQUIRE(actual[0] == 2.0);
        STATIC_REQUIRE(actual[1] == 4.0);
        STATIC_REQUIRE(actual[2] == 6.0);
    }
}

TEST_CASE("test vector of integers", "[labo_9][vector3d]")
{
    constexpr linalg::Vector3D test_vec_1{linalg::X{1}, linalg::Y{2}, linalg::Z{3}};
    constexpr linalg::Vector3D test_vec_2{linalg::X{3}, linalg::Y{1}, linalg::Z{2}};

    SECTION("access values using the index operator")
    {
        STATIC_REQUIRE(test_vec_1[0] == test_vec_1.x().get());
        STATIC_REQUIRE(test_vec_1[1] == test_vec_1.y().get());
        STATIC_REQUIRE(test_vec_1[2] == test_vec_1.z().get());
    }

    SECTION("attempt to access invalid index")
    {
        REQUIRE_THROWS_MATCHES(
            test_vec_1[3],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("index must be 0, 1, 2"))
        );
    }

    SECTION("compare vectors")
    {
        STATIC_REQUIRE(test_vec_1 == test_vec_1);
        STATIC_REQUIRE(test_vec_1 != test_vec_2);
        STATIC_REQUIRE_FALSE(test_vec_1 == test_vec_2);
        STATIC_REQUIRE_FALSE(test_vec_1 != test_vec_1);
    }

    SECTION("add vectors")
    {
        constexpr auto actual = test_vec_1 + test_vec_2;

        STATIC_REQUIRE(actual[0] == 4);
        STATIC_REQUIRE(actual[1] == 3);
        STATIC_REQUIRE(actual[2] == 5);
    }

    SECTION("subtract vectors")
    {
        constexpr auto actual = test_vec_1 - test_vec_2;

        STATIC_REQUIRE(actual[0] == -2);
        STATIC_REQUIRE(actual[1] == 1);
        STATIC_REQUIRE(actual[2] == 1);
    }

    SECTION("multiply by scalar")
    {
        constexpr auto actual = test_vec_1 * 2;

        STATIC_REQUIRE(actual[0] == 2);
        STATIC_REQUIRE(actual[1] == 4);
        STATIC_REQUIRE(actual[2] == 6);
    }
}
