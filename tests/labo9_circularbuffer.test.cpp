#include <catch.hpp>

import circularbuffer;
import cpprog;

namespace {

template <typename T, int N>
constexpr void fill(CircularBuffer<T, N>& buffer, T const& value)
{
    for (int i{0}; i < N; ++i)
    {
        buffer.push_back(value);
    }
}

} // namespace

TEST_CASE("circular buffer basics", "[labo_9][circular_buffer]")
{
    CircularBuffer<int, 5> buffer{};

    SECTION("can be created and destroyed")
    {
    }

    SECTION("is empty after creation")
    {
        REQUIRE(buffer.is_empty());
    }

    SECTION("is not full after creation")
    {
        REQUIRE_FALSE(buffer.is_full());
    }

    SECTION("is not empty after push")
    {
        buffer.push_back(42);

        REQUIRE_FALSE(buffer.is_empty());
    }

    SECTION("is empty after push then pop")
    {
        buffer.push_back(42);
        buffer.pop_front();

        REQUIRE(buffer.is_empty());
    }

    SECTION("pop equals push for one item")
    {
        buffer.push_back(42);
        REQUIRE(buffer.pop_front() == 42);
    }

    SECTION("push pop is fifo")
    {
        buffer.push_back(41);
        buffer.push_back(42);
        buffer.push_back(43);

        REQUIRE(buffer.pop_front() == 41);
        REQUIRE(buffer.pop_front() == 42);
        REQUIRE(buffer.pop_front() == 43);
    }

    SECTION("fill to capacity")
    {
        fill(buffer, 42);

        REQUIRE(buffer.is_full());
    }

    SECTION("is not full after pop from full buffer")
    {
        fill(buffer, 42);
        buffer.pop_front();

        REQUIRE_FALSE(buffer.is_full());
    }
}

TEST_CASE("circular buffer wrapping", "[labo_9][circular_buffer]")
{
    CircularBuffer<int, 2> buffer{};

    SECTION("force a buffer wraparound")
    {
        buffer.push_back(1);
        buffer.push_back(2);
        buffer.pop_front();
        buffer.push_back(3);

        REQUIRE(buffer.pop_front() == 2);
        REQUIRE(buffer.pop_front() == 3);
        REQUIRE(buffer.is_empty());
    }

    SECTION("full after wrapping")
    {
        buffer.push_back(1);
        buffer.push_back(2);
        buffer.pop_front();
        buffer.push_back(3);

        REQUIRE(buffer.is_full());
    }
}

TEST_CASE("circular buffer exceptional cases", "[labo_9][circular_buffer]")
{
    CircularBuffer<int, 2> buffer{};

    SECTION("push to full violates precondition")
    {
        buffer.push_back(41);
        buffer.push_back(42);

        REQUIRE_THROWS_MATCHES(
            buffer.push_back(43),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("cannot push to full buffer"))
        );
    }

    SECTION("pop from empty violates precondition")
    {
        REQUIRE_THROWS_MATCHES(
            buffer.pop_front(),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("cannot pop from empty buffer"))
        );
    }
}
