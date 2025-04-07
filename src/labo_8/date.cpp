export module datetime:date;

import :yearmonthday;
import :leapyear;
import :verification;
import cpprog;
import std;

namespace datetime {

export class Date
{
public:
    constexpr Date() = default;

    constexpr Date(Year year, Month month, Day day) : year_{year}, month_{month}, day_{day}
    {
        cpprog::expect([&] { return is_valid_date(year, month, day); }, "Invalid date!");
    }

    constexpr Date(Day day, Month month, Year year) : Date(year, month, day) {}
    constexpr Date(Month month, Day day, Year year) : Date(year, month, day) {}

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

export constexpr Date& operator++(Date& date)
{
    auto const current_month_days = (date.month() == Month::feb) ? days_in_february(date.year()) : days_in_month(date.month());

    auto next_year = date.year().get();
    auto next_month = date.month();
    auto next_day = date.day().get() + 1;

    if (current_month_days < next_day)
    {
        next_day = 1;

        if (++next_month == Month::jan) { ++next_year; }
    }

    return date = Date{Year{next_year}, next_month, Day{next_day}};
}

export constexpr Date& operator+=(Date& date, int days)
{
    cpprog::expect([&] { return 0 <= days; }, "Days must be positive");

    for (int i{0}; i < days; ++i) { ++date; }
    return date;
}

} // namespace datetime
