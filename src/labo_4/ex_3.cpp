import datetime;
import std;

int main()
try
{
    using datetime::Year;
    using datetime::Month;
    using datetime::Day;

    [[maybe_unused]] datetime::Date const date_1{Year{2025}, Month::feb, Day{28}};
    [[maybe_unused]] datetime::Date const date_2{Day{28}, Month::feb, Year{2025}};
    [[maybe_unused]] datetime::Date const date_3{Month::feb, Day{28}, Year{2025}};

    return 0;
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
