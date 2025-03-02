import datetime;
import std;

int main()
try
{
    using datetime::Year;
    using datetime::Month;
    using datetime::Day;

    static constexpr datetime::Date start_day_1{Year{2025}, Month::feb, Day{27}};
    static constexpr datetime::Date const end_day_1{Year{2025}, Month::feb, Day{28}};
    static_assert(start_day_1 < end_day_1);

    static constexpr datetime::Date start_day_2{Year{2025}, Month::feb, Day{28}};
    static constexpr datetime::Date const end_day_2{Year{2025}, Month::mar, Day{1}};
    static_assert(end_day_2 > start_day_2);

    // uncomment the following line to try an invalid date, compiler error
    // static constexpr datetime::Date invalid_day{Year{2025}, Month::feb, Day{29}};

    return 0;
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
