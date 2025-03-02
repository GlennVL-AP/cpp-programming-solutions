export module datetime;

import cpprog;
import std;

namespace datetime {

export class Year
{
public:
    explicit Year(int year) : year_{year} {}

    [[nodiscard]] int get() const { return year_; }

    [[nodiscard]] int& get() { return year_; }

private:
    int year_{};
};

export class Day
{
public:
    explicit Day(int day) : day_{day} {}

    [[nodiscard]] int get() const { return day_; }

    [[nodiscard]] int& get() { return day_; }

private:
    int day_{};
};

export enum class Month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };

export Month month_from_int(int month)
{
    cpprog::expect(
        [&] { return (std::to_underlying(Month::jan) <= month) && (month <= std::to_underlying(Month::dec)); }, "invalid month"
    );

    return Month{month};
}

export Month operator++(Month& month)
{
    month = (month == Month::dec) ? Month::jan : Month{std::to_underlying(month) + 1};
    return month;
}

export bool is_valid_date([[maybe_unused]] Year year, [[maybe_unused]] Month month, [[maybe_unused]] Day day)
{
    return true;
}

export class Date
{
public:
    Date() = default;

    Date(Year year, Month month, Day day) : year_{year}, month_{month}, day_{day}
    {
        cpprog::expect([&] { return is_valid_date(year, month, day); }, "Invalid date!");
    }

    [[nodiscard]] Year year() const { return year_; }

    [[nodiscard]] Month month() const { return month_; }

    [[nodiscard]] Day day() const { return day_; }

private:
    static constexpr auto epoch_year{1'970};
    static constexpr auto epoch_month{Month::jan};
    static constexpr auto epoch_day{1};

    Year year_{epoch_year};
    Month month_{epoch_month};
    Day day_{epoch_day};
};

export bool operator==(Date const& rhs, Date const& lhs)
{
    return (lhs.year().get() == rhs.year().get()) && (lhs.month() == rhs.month()) && (lhs.day().get() == rhs.day().get());
}

export bool operator!=(Date const& rhs, Date const& lhs)
{
    return !(lhs == rhs);
}

} // namespace datetime
