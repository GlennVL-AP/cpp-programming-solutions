import datetime;
import std;

int main()
try
{
    std::print("Geef een jaar, maand, en dag: ");

    int year{};
    int month{};
    int day{};
    std::cin >> year >> month >> day;

    if (datetime::is_valid_date(datetime::Year{year}, datetime::Month{month}, datetime::Day{day}))
    {
        std::println("{}-{}-{} is een geldige datum", day, month, year);
    }
    else
    {
        std::println("{}-{}-{} is geen geldige datum", day, month, year);
    }

    return 0;
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
