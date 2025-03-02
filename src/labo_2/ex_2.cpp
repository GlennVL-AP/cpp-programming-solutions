import std;

double mile_to_km(double mile)
{
    static constexpr double km_per_mile{1.609};
    return mile * km_per_mile;
}

int main() // NOLINT(bugprone-exception-escape)
{
    std::println("Geef een aantal mijl: ");

    double miles{};
    std::cin >> miles;

    std::println("{} mi = {} km", miles, mile_to_km(miles));
}
