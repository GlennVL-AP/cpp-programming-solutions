export module datetime:leapyear;

import :yearmonthday;
import cpprog;
import std;

namespace datetime {

export [[nodiscard]] constexpr bool is_leap_year(Year year)
{
    static constexpr int leap_year{4};
    static constexpr int not_leap_year{100};
    static constexpr int not_leap_year_exception{400};

    return ((year.get() % leap_year == 0) && (year.get() % not_leap_year != 0)) || (year.get() % not_leap_year_exception == 0);
}

export [[nodiscard]] constexpr int days_in_month(Month month)
{
    cpprog::expect([&] { return (Month::jan <= month) && (month <= Month::dec); }, "Month must be valid");
    cpprog::expect([&] { return month != Month::feb; }, "Does not work for february");

    static constexpr std::array days_per_month{31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return days_per_month.at(static_cast<std::size_t>(std::to_underlying(month)) - 1);
}

export [[nodiscard]] constexpr int days_in_february(Year year)
{
    static constexpr int feb_days{28};
    static constexpr int feb_leap_days{29};

    return is_leap_year(year) ? feb_leap_days : feb_days;
}

} // namespace datetime
