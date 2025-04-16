#include <catch.hpp>

import cpprog;
import matrix;
import std;

TEST_CASE("test creating matrix", "[labo_9][matrix]")
{
    SECTION("default constructed matrix is all zero")
    {
        constexpr linalg::Matrix<double, 2, 3> mx_1{};
        for (int i{0}; i < 2; ++i)
        {
            for (int j{0}; j < 3; ++j)
            {
                REQUIRE(mx_1[i,j] == 0.0);
            }
        }

        constexpr linalg::Matrix<int, 4, 5> mx_2{};
        for (int i{0}; i < 4; ++i)
        {
            for (int j{0}; j < 5; ++j)
            {
                REQUIRE(mx_2[i,j] == 0);
            }
        }
    }

    SECTION("fill matrix with value")
    {
        constexpr std::complex value{std::numbers::e, std::numbers::pi};
        constexpr linalg::Matrix<std::complex<double>, 6, 7> mx(value);

        for (int i{0}; i < 6; ++i)
        {
            for (int j{0}; j < 7; ++j)
            {
                REQUIRE(mx[i,j] == value);
            }
        }
    }

    SECTION("construct matrix from intializer list")
    {
        constexpr linalg::Matrix<double, 3, 2> mx{
            1.0, 2.0,
            3.0, 4.0,
            5.0, 6.0
        };

        STATIC_REQUIRE(mx[0,0] == 1.0);
        STATIC_REQUIRE(mx[0,1] == 2.0);
        STATIC_REQUIRE(mx[1,0] == 3.0);
        STATIC_REQUIRE(mx[1,1] == 4.0);
        STATIC_REQUIRE(mx[2,0] == 5.0);
        STATIC_REQUIRE(mx[2,1] == 6.0);
    }

    SECTION("attempt to construct matrix from wrong size initializer list")
    {
        REQUIRE_THROWS_MATCHES(
            (linalg::Matrix<double, 3, 2>{1.0, 2.0, 3.0}),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("requires MxN items"))
        );
    }

    SECTION("attempt to access invalid index")
    {
        constexpr linalg::Matrix<double, 3, 2> mx{
            1.0, 2.0,
            3.0, 4.0,
            5.0, 6.0
        };

        REQUIRE_THROWS_MATCHES(
            (mx[-1,0]),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= i < M"))
        );

        REQUIRE_THROWS_MATCHES(
            (mx[3,0]),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= i < M"))
        );

        REQUIRE_THROWS_MATCHES(
            (mx[0,-1]),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= j < N"))
        );

        REQUIRE_THROWS_MATCHES(
            (mx[0,2]),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= j < N"))
        );
    }
}

TEST_CASE("test getting matrix rows and columns", "[labo_9][matrix]")
{
    constexpr linalg::Matrix<double, 3, 2> mx{
        1.0, 2.0,
        3.0, 4.0,
        5.0, 6.0
    };

    SECTION("test getting rows")
    {
        STATIC_REQUIRE(mx.row(0) == std::array{1.0, 2.0});
        STATIC_REQUIRE(mx.row(1) == std::array{3.0, 4.0});
        STATIC_REQUIRE(mx.row(2) == std::array{5.0, 6.0});
    }

    SECTION("attempt to get invalid row")
    {
        REQUIRE_THROWS_MATCHES(
            mx.row(-1),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= row_index < M"))
        );

        REQUIRE_THROWS_MATCHES(
            mx.row(3),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= row_index < M"))
        );
    }

    SECTION("test getting columns")
    {
        STATIC_REQUIRE(mx.column(0) == std::array{1.0, 3.0, 5.0});
        STATIC_REQUIRE(mx.column(1) == std::array{2.0, 4.0, 6.0});
    }

    SECTION("attempt to get invalid column")
    {
        REQUIRE_THROWS_MATCHES(
            mx.column(-1),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= col_index < N"))
        );

        REQUIRE_THROWS_MATCHES(
            mx.column(2),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= col_index < N"))
        );
    }
}

TEST_CASE("test comparing matrices", "[labo_9][matrix]")
{
    constexpr linalg::Matrix<double, 3, 2> mx_1{
        1.0, 2.0,
        3.0, 4.0,
        5.0, 6.0
    };

    constexpr linalg::Matrix<double, 3, 2> mx_2{
        1.0, 2.0,
        4.0, 3.0,
        5.0, 6.0
    };


    SECTION("test equals operator")
    {
        STATIC_REQUIRE(mx_1 == auto{mx_1});
        STATIC_REQUIRE_FALSE(mx_1 == mx_2);
    }

    SECTION("test not equals operator")
    {
        STATIC_REQUIRE_FALSE(mx_1 != auto{mx_1});
        STATIC_REQUIRE(mx_1 != mx_2);
    }
}

TEST_CASE("test matrix arithmetic", "[labo_9][matrix]")
{
    constexpr linalg::Matrix<int, 3, 2> mx_1{
        1, 2,
        3, 4,
        5, 6
    };

    constexpr linalg::Matrix<int, 3, 2> mx_2{
        7, 8,
        9, 10,
        11, 12
    };

    constexpr linalg::Matrix<int, 2, 3> mx_3{
        1, 2, 3,
        4, 5, 6
    };

    SECTION("addition")
    {
        constexpr linalg::Matrix<int, 3, 2> expected{
            8, 10,
            12, 14,
            16, 18
        };

        STATIC_REQUIRE(mx_1 + mx_2 == expected);
    }

    SECTION("subtraction")
    {
        constexpr linalg::Matrix<int, 3, 2> expected{
            -6, -6,
            -6, -6,
            -6, -6
        };

        STATIC_REQUIRE(mx_1 - mx_2 == expected);
    }

    SECTION("linalg::Matrix multiplication")
    {
        constexpr linalg::Matrix<int, 3, 3> expected{
            9, 12, 15,
            19, 26, 33,
            29, 40, 51
        };

        STATIC_REQUIRE(mx_1 * mx_3 == expected);
    }

    SECTION("multiply by scaler")
    {
        constexpr linalg::Matrix<int, 2, 3> expected{
            2, 4, 6,
            8, 10, 12
        };

        STATIC_REQUIRE(mx_3 * 2 == expected);
    }
}

TEST_CASE("test calculating determinant", "[labo_9][matrix]")
{
    SECTION("two by two matrix")
    {
        constexpr linalg::Matrix<double, 2, 2> mx{
            1.0, 2.0,
            3.0, 4.0
        };

        REQUIRE_THAT(determinant(mx), Catch::Matchers::WithinAbs(-2.0, 0.000001));
    }

    SECTION("four by four matrix")
    {
        constexpr linalg::Matrix<double, 3, 3> mx{
            1.0, 2.0, 3.0,
            4.0, 5.0, 6.0,
            7.0, 8.0, 9.0
        };

        REQUIRE_THAT(determinant(mx), Catch::Matchers::WithinAbs(0.0, 0.000001));
    }
}

TEST_CASE("test transposing matrices", "[labo_9][matrix]")
{
    constexpr linalg::Matrix<double, 3, 2> mx_1{
        1.0, 2.0,
        3.0, 4.0,
        5.0, 6.0
    };

    constexpr linalg::Matrix<double, 2, 3> mx_2{
        1.0, 3.0, 5.0,
        2.0, 4.0, 6.0
    };

    STATIC_REQUIRE(transpose(transpose(mx_1)) == mx_1);
    STATIC_REQUIRE(transpose(transpose(mx_2)) == mx_2);
    STATIC_REQUIRE(transpose(mx_1) == mx_2);
    STATIC_REQUIRE(transpose(mx_2) == mx_1);
}
