#include <catch.hpp>

import cpprog;
import datetime;
import std;

TEST_CASE("test leap year detection", "[labo_4][datetime]")
{
    SECTION("leap years are checked correctly")
    {
        STATIC_REQUIRE(datetime::is_leap_year(datetime::Year{1'600}));
        STATIC_REQUIRE_FALSE(datetime::is_leap_year(datetime::Year{1'700}));
        STATIC_REQUIRE_FALSE(datetime::is_leap_year(datetime::Year{1'800}));
        STATIC_REQUIRE_FALSE(datetime::is_leap_year(datetime::Year{1'900}));
        STATIC_REQUIRE(datetime::is_leap_year(datetime::Year{2'000}));
        STATIC_REQUIRE(datetime::is_leap_year(datetime::Year{2'004}));
        STATIC_REQUIRE_FALSE(datetime::is_leap_year(datetime::Year{2'005}));
    }
}

TEST_CASE("check if date is valid", "[labo_4][datetime]")
{
    using datetime::Day;
    using datetime::Month;
    using datetime::Year;

    SECTION("invalid months are detected")
    {
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'400}, Month{0}, Day{1}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'400}, Month{1}, Day{1}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'400}, Month{12}, Day{31}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'400}, Month{13}, Day{1}));
    }

    SECTION("invalid days are detected")
    {
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'500}, Month{1}, Day{-1}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'500}, Month{1}, Day{0}));
    }

    SECTION("february has 29 days in leap years")
    {
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'600}, Month{2}, Day{29}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'700}, Month{2}, Day{30}));
    }

    SECTION("february has 28 years in non-leap years")
    {
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'700}, Month{2}, Day{28}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'700}, Month{2}, Day{29}));
    }

    SECTION("month length is correct")
    {
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'800}, Month{1}, Day{31}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'800}, Month{1}, Day{32}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'800}, Month{3}, Day{31}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'800}, Month{3}, Day{32}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'800}, Month{4}, Day{30}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'800}, Month{4}, Day{31}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'800}, Month{5}, Day{31}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'800}, Month{5}, Day{32}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'800}, Month{6}, Day{30}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'800}, Month{6}, Day{31}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'800}, Month{7}, Day{31}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'800}, Month{7}, Day{32}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'800}, Month{8}, Day{31}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'800}, Month{8}, Day{32}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'800}, Month{9}, Day{30}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'800}, Month{9}, Day{31}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'800}, Month{10}, Day{31}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'800}, Month{10}, Day{32}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'800}, Month{11}, Day{30}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'800}, Month{11}, Day{31}));
        STATIC_REQUIRE(datetime::is_valid_date(Year{1'800}, Month{12}, Day{31}));
        STATIC_REQUIRE_FALSE(datetime::is_valid_date(Year{1'800}, Month{12}, Day{32}));
    }
}

TEST_CASE("date class tests", "[labo_4][datetime]")
{
    using datetime::Day;
    using datetime::Month;
    using datetime::Year;

    SECTION("date object is default constructed to epoch time")
    {
        static constexpr datetime::Date epoch_time{};

        STATIC_REQUIRE(epoch_time.year() == Year{1'970});
        STATIC_REQUIRE(epoch_time.month() == Month::jan);
        STATIC_REQUIRE(epoch_time.day() == Day{1});
    }

    SECTION("date object can be constructed from valid date")
    {
        REQUIRE_NOTHROW(datetime::Date{Year{2'025}, Month::feb, Day{28}});
        REQUIRE_NOTHROW(datetime::Date{Day{28}, Month::feb, Year{2'025}});
        REQUIRE_NOTHROW(datetime::Date{Month::feb, Day{28}, Year{2'025}});
    }

    SECTION("date constructor throws when date is invalid")
    {
        REQUIRE_THROWS_MATCHES(
            (datetime::Date{Year{2'025}, Month::feb, Day{29}}),
            cpprog::ExpectError,
            Catch::Matchers::MessageMatches(Catch::Matchers::EndsWith("Invalid date!"))
        );
    }
}

TEST_CASE("test comparing dates", "[labo_4][datetime]")
{
    using datetime::Day;
    using datetime::Month;
    using datetime::Year;

    SECTION("equality")
    {
        static constexpr datetime::Date feb_27{Year{2'025}, Month::feb, Day{27}};
        static constexpr datetime::Date feb_28{Year{2'025}, Month::feb, Day{28}};

        STATIC_REQUIRE(feb_27 == feb_27);
        STATIC_REQUIRE_FALSE(feb_27 == feb_28);
        STATIC_REQUIRE_FALSE(feb_27 != feb_27);
        STATIC_REQUIRE(feb_27 != feb_28);
    }

    SECTION("smaller than")
    {
        static constexpr datetime::Date feb_27{Year{2'025}, Month::feb, Day{27}};
        static constexpr datetime::Date feb_28{Year{2'025}, Month::feb, Day{28}};

        STATIC_REQUIRE(feb_27 < feb_28);
        STATIC_REQUIRE_FALSE(feb_28 < feb_27);
    }
}

TEST_CASE("test incrementing dates", "[labo_4][datetime]")
{
    using datetime::Day;
    using datetime::Month;
    using datetime::Year;

    SECTION("increment day does not overflow")
    {
        static constexpr datetime::Date expected{Year{2'025}, Month::feb, Day{28}};

        datetime::Date test{Year{2'025}, Month::feb, Day{27}};
        REQUIRE(++test == expected);
    }

    SECTION("incrementing day overflows month")
    {
        static constexpr datetime::Date expected{Year{2'025}, Month::mar, Day{1}};

        datetime::Date test{Year{2'025}, Month::feb, Day{28}};
        REQUIRE(++test == expected);
    }

    SECTION("incrementing day overflows year")
    {
        static constexpr datetime::Date expected{Year{2'026}, Month::jan, Day{1}};

        datetime::Date test{Year{2'025}, Month::dec, Day{31}};
        REQUIRE(++test == expected);
    }

    SECTION("increment by multiple days at once")
    {
        static constexpr datetime::Date expected{Year{2'026}, Month::jan, Day{1}};

        datetime::Date test{Year{2'025}, Month::dec, Day{28}};
        test += 4;
        REQUIRE(test == expected);
    }
}

TEST_CASE("date class properties", "[labo_4][datetime]")
{
    SECTION("check type traits")
    {
        STATIC_REQUIRE(std::is_class_v<datetime::Date>);
        STATIC_REQUIRE(std::is_standard_layout_v<datetime::Date>);
        STATIC_REQUIRE(std::is_implicit_lifetime_v<datetime::Date>);
        STATIC_REQUIRE(std::is_default_constructible_v<datetime::Date>);
        STATIC_REQUIRE(std::is_trivially_destructible_v<datetime::Date>);
        STATIC_REQUIRE(std::is_copy_constructible_v<datetime::Date>);
        STATIC_REQUIRE(std::is_copy_assignable_v<datetime::Date>);
        STATIC_REQUIRE(std::is_trivially_copyable_v<datetime::Date>);
        STATIC_REQUIRE(std::is_move_constructible_v<datetime::Date>);
        STATIC_REQUIRE(std::is_move_assignable_v<datetime::Date>);
    }
}
