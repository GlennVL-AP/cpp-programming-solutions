export module datetime:yearmonthday;

import cpprog;
import std;

namespace datetime {

export class Year
{
public:
    constexpr explicit Year(int year) : year_{year} {}

    [[nodiscard]] constexpr int get() const { return year_; }
    [[nodiscard]] constexpr int& get() { return year_; }

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

} // namespace datetime
