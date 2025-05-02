#include <catch.hpp>

import cpprog;
import dynarray;
import std;

namespace {

// std::ranges::iota is missing in the clang standard library
template <std::weakly_incrementable T, std::ranges::output_range<T const&> R>
void iota(R const& range, T value)
{
    std::iota(std::ranges::begin(range), std::ranges::end(range), std::move(value)); // NOLINT(modernize-use-ranges)
}

} // namespace

TEST_CASE("test dynamic array with raw pointers", "[labo_10][dynamic_array]")
{
    using rawptr::DynamicArray;
    DynamicArray<int> const empty_array{};
    DynamicArray<int> array{3};

    SECTION("can be created and destroyed")
    {
    }

    SECTION("is default initialized after creation")
    {
        for (int i{0}; i < array.size(); ++i)
        {
            REQUIRE(array[i] == 0);
        }
    }

    SECTION("first item can be updated")
    {
        array[0] = 5;
        REQUIRE(array[0] == 5);
    }

    SECTION("last item can be updated")
    {
        array[array.size()-1] = 5;
        REQUIRE(array[array.size()-1] == 5);
    }

    SECTION("accessing before begin violates precondition")
    {
        REQUIRE_THROWS_MATCHES(
            array[-1],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= index < size()"))
        );
        REQUIRE_THROWS_MATCHES(
            std::as_const(array)[-1],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= index < size()"))
        );
    }

    SECTION("accessing past end violates precondition")
    {
        REQUIRE_THROWS_MATCHES(
            array[array.size()],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= index < size()"))
        );

        REQUIRE_THROWS_MATCHES(
            std::as_const(array)[array.size()],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= index < size()"))
        );
    }

    SECTION("dynamic array is a range")
    {
        iota(array, 0);
        for (int i{0}; i < array.size(); ++i)
        {
            REQUIRE(array[i] == i);
        }
    }

    SECTION("copy constructor")
    {
        iota(array, 0);
        auto const copy = array;
        REQUIRE(copy == array);
    }

    SECTION("copy assignment")
    {
        iota(array, 0);
        auto copy = array;
        REQUIRE(copy == array);
    }

    SECTION("move constructor")
    {
        iota(array, 0);
        auto copy = array;

        auto const actual = std::move(copy);

        REQUIRE(copy == empty_array);
        REQUIRE(actual == array);
    }

    SECTION("move assignment")
    {
        iota(array, 0);
        auto copy = array;
        auto actual = empty_array;

        actual = std::move(copy);

        REQUIRE(copy == empty_array);
        REQUIRE(actual == array);
    }

    SECTION("array with size zero")
    {
        REQUIRE(empty_array.size() == 0);
        REQUIRE(empty_array.begin() == empty_array.end());

        REQUIRE_THROWS_MATCHES(
            empty_array[0],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= index < size()"))
        );
    }

    SECTION("adding two arrays")
    {
        DynamicArray<int> const another_array{10};
        iota(another_array, array.size());
        iota(array, 0);
        DynamicArray<int> const expected{another_array.size() + array.size()};
        iota(expected, 0);

        REQUIRE(empty_array + empty_array == empty_array);
        REQUIRE(empty_array + array == array);
        REQUIRE(array + empty_array == array);
        REQUIRE(array + another_array == expected);
    }

    SECTION("adding one array to another")
    {
        DynamicArray<int> const another_array{10};
        iota(another_array, array.size());
        iota(array, 0);
        DynamicArray<int> const expected{another_array.size() + array.size()};
        iota(expected, 0);

        auto actual = empty_array;
        actual += empty_array;
        actual += array;
        actual += another_array;
        actual += empty_array;

        REQUIRE(actual == expected);
    }
}

TEST_CASE("test dynamic array with unique_ptr", "[labo_10][dynamic_array]")
{
    using uniqueptr::DynamicArray;
    DynamicArray<int> const empty_array{};
    DynamicArray<int> array{3};

    SECTION("can be created and destroyed")
    {
    }

    SECTION("is default initialized after creation")
    {
        for (int i{0}; i < array.size(); ++i)
        {
            REQUIRE(array[i] == 0);
        }
    }

    SECTION("first item can be updated")
    {
        array[0] = 5;
        REQUIRE(array[0] == 5);
    }

    SECTION("last item can be updated")
    {
        array[array.size()-1] = 5;
        REQUIRE(array[array.size()-1] == 5);
    }

    SECTION("accessing before begin violates precondition")
    {
        REQUIRE_THROWS_MATCHES(
            array[-1],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= index < size()"))
        );
        REQUIRE_THROWS_MATCHES(
            std::as_const(array)[-1],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= index < size()"))
        );
    }

    SECTION("accessing past end violates precondition")
    {
        REQUIRE_THROWS_MATCHES(
            array[array.size()],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= index < size()"))
        );

        REQUIRE_THROWS_MATCHES(
            std::as_const(array)[array.size()],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= index < size()"))
        );
    }

    SECTION("dynamic array is a range")
    {
        iota(array, 0);
        for (int i{0}; i < array.size(); ++i)
        {
            REQUIRE(array[i] == i);
        }
    }

    SECTION("copy constructor")
    {
        iota(array, 0);
        auto const copy = array;
        REQUIRE(copy == array);
    }

    SECTION("copy assignment")
    {
        iota(array, 0);
        auto copy = array;
        REQUIRE(copy == array);
    }

    SECTION("move constructor")
    {
        iota(array, 0);
        auto copy = array;

        auto const actual = std::move(copy);

        REQUIRE(copy == empty_array);
        REQUIRE(actual == array);
    }

    SECTION("move assignment")
    {
        iota(array, 0);
        auto copy = array;
        auto actual = empty_array;

        actual = std::move(copy);

        REQUIRE(copy == empty_array);
        REQUIRE(actual == array);
    }

    SECTION("array with size zero")
    {
        REQUIRE(empty_array.size() == 0);
        REQUIRE(empty_array.begin() == empty_array.end());

        REQUIRE_THROWS_MATCHES(
            empty_array[0],
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("0 <= index < size()"))
        );
    }

    SECTION("adding two arrays")
    {
        DynamicArray<int> const another_array{10};
        iota(another_array, array.size());
        iota(array, 0);
        DynamicArray<int> const expected{another_array.size() + array.size()};
        iota(expected, 0);

        REQUIRE(empty_array + empty_array == empty_array);
        REQUIRE(empty_array + array == array);
        REQUIRE(array + empty_array == array);
        REQUIRE(array + another_array == expected);
    }

    SECTION("adding one array to another")
    {
        DynamicArray<int> const another_array{10};
        iota(another_array, array.size());
        iota(array, 0);
        DynamicArray<int> const expected{another_array.size() + array.size()};
        iota(expected, 0);

        auto actual = empty_array;
        actual += empty_array;
        actual += array;
        actual += another_array;
        actual += empty_array;

        REQUIRE(actual == expected);
    }
}
