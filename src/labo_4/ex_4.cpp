import cpprog;
import datetime;
import std;

int main()
try
{
    using datetime::Year;
    using datetime::Month;
    using datetime::Day;

    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    datetime::Date start_day_1{Year{2025}, Month::feb, Day{27}};
    datetime::Date const end_day_1{Year{2025}, Month::feb, Day{28}};
    cpprog::expect([&] { return ++start_day_1 == end_day_1; }, "oops");

    datetime::Date start_day_2{Year{2025}, Month::feb, Day{28}};
    datetime::Date const end_day_2{Year{2025}, Month::mar, Day{1}};
    cpprog::expect([&] { return ++start_day_2 == end_day_2; }, "oops");

    datetime::Date start_day_3{Year{2025}, Month::dec, Day{31}};
    datetime::Date const end_day_3{Year{2026}, Month::jan, Day{1}};
    cpprog::expect([&] { return ++start_day_3 == end_day_3; }, "oops");

    datetime::Date start_day_4{Year{2023}, Month::feb, Day{28}};
    datetime::Date const end_day_4{Year{2024}, Month::feb, Day{29}};
    cpprog::expect([&] { return (start_day_4 += 366) == end_day_4; }, "oops");

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    return 0;
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
