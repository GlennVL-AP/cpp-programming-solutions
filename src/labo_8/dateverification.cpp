export module datetime:verification;

import :yearmonthday;
import :leapyear;

namespace datetime {

export [[nodiscard]] constexpr bool is_valid_date(Year year, Month month, Day day)
{
    return (0 < day.get()) && (Month::jan <= month) && (month <= Month::dec)
           && (day.get() <= ((month == Month::feb) ? days_in_february(year) : days_in_month(month)));
}

} // namespace datetime
