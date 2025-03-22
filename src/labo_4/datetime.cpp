export module datetime;

import cpprog;
import std;

namespace datetime {

export class Year
{
public:
    constexpr explicit Year(int year) : year_{year} {}

    [[nodiscard]] constexpr int get() const { return year_; }
    [[nodiscard]] constexpr int& get() { return year_; }

    // labo 4 exercise 5
    [[nodiscard]] constexpr auto operator<=>(Year const&) const = default;

private:
    int year_{};
};

export class Day
{
public:
    constexpr explicit Day(int day) : day_{day} {}

    [[nodiscard]] constexpr int get() const { return day_; }
    [[nodiscard]] constexpr int& get() { return day_; }

    // labo 4 exercise 5
    [[nodiscard]] constexpr auto operator<=>(Day const&) const = default;

private:
    int day_{};
};

export enum class Month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

export [[nodiscard]] constexpr Month month_from_int(int month)
{
    cpprog::expect(
        [&] { return (std::to_underlying(Month::jan) <= month) && (month <= std::to_underlying(Month::dec)); }, "invalid month"
    );

    return Month{month};
}

export constexpr Month& operator++(Month& month)
{
    return month = (month == Month::dec) ? Month::jan : Month{std::to_underlying(month) + 1};
}

// labo 4 exercise 1
export [[nodiscard]] constexpr bool is_leap_year(Year year)
{
    static constexpr int leap_year{4};
    static constexpr int not_leap_year{100};
    static constexpr int not_leap_year_exception{400};

    return ((year.get() % leap_year == 0) && (year.get() % not_leap_year != 0)) || (year.get() % not_leap_year_exception == 0);
}

namespace {

// labo 4 exercise 1
[[nodiscard]] constexpr int days_in_month(Month month)
{
    cpprog::expect([&] { return (Month::jan <= month) && (month <= Month::dec); }, "Month must be valid");
    cpprog::expect([&] { return month != Month::feb; }, "Does not work for february");

    static constexpr std::array days_per_month{31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return days_per_month.at(static_cast<std::size_t>(std::to_underlying(month)) - 1);
}

// labo 4 exercise 1
[[nodiscard]] constexpr int days_in_february(Year year)
{
    static constexpr int feb_days{28};
    static constexpr int feb_leap_days{29};

    return is_leap_year(year) ? feb_leap_days : feb_days;
}

} // namespace

// labo 4 exercise 1
export [[nodiscard]] constexpr bool is_valid_date(Year year, Month month, Day day)
{
    if ((day.get() <= 0) || (month < Month::jan) || (Month::dec < month))
    {
        return false;
    }

    return day.get() <= ((month == Month::feb) ? days_in_february(year) : days_in_month(month));
}

export class Date
{
public:
    constexpr Date() = default;

    constexpr Date(Year year, Month month, Day day) : year_{year}, month_{month}, day_{day}
    {
        cpprog::expect([&] { return is_valid_date(year, month, day); }, "Invalid date!");
    }

    // labo 4 exercise 3
    constexpr Date(Day day, Month month, Year year) : Date(year, month, day) {}
    constexpr Date(Month month, Day day, Year year) : Date(year, month, day) {}

    // labo 4 exercise 5
    [[nodiscard]] constexpr auto operator<=>(Date const&) const = default;

    [[nodiscard]] constexpr Year year() const { return year_; }
    [[nodiscard]] constexpr Month month() const { return month_; }
    [[nodiscard]] constexpr Day day() const { return day_; }

private:
    static constexpr auto epoch_year{1'970};
    static constexpr auto epoch_month{Month::jan};
    static constexpr auto epoch_day{1};

    Year year_{epoch_year};
    Month month_{epoch_month};
    Day day_{epoch_day};
};

// following lines are no longer needed when operator<=> is added
/*export [[nodiscard]] constexpr bool operator==(Date const& lhs, Date const& rhs)
{
    return (lhs.year().get() == rhs.year().get()) && (lhs.month() == rhs.month()) && (lhs.day().get() == rhs.day().get());
}

export [[nodiscard]] constexpr bool operator!=(Date const& lhs, Date const& rhs)
{
    return !(lhs == rhs);
}*/

// labo 4 exercise 4
export constexpr Date& operator++(Date& date)
{
    auto const current_month_days = (date.month() == Month::feb) ? days_in_february(date.year()) : days_in_month(date.month());

    auto next_year = date.year().get();
    auto next_month = date.month();
    auto next_day = date.day().get() + 1;

    if (current_month_days < next_day)
    {
        next_day = 1;

        if (++next_month == Month::jan)
        {
            ++next_year;
        }
    }

    return date = Date{Year{next_year}, next_month, Day{next_day}};
}

// labo 4 exercise 4
export constexpr Date& operator+=(Date& date, int days)
{
    cpprog::expect([&] { return 0 <= days; }, "Days must be positive");

    for (int i{0}; i < days; ++i) { ++date; }
    return date;
}

} // namespace datetime
