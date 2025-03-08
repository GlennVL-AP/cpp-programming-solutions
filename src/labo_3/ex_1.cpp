import std;

double ctok(double celsius)
{
    static constexpr double kelvin_offset{273.15};
    return celsius + kelvin_offset;
}

int main()
try
{
    double celsius{0.0};
    std::cin >> celsius;
    double const kelvin{ctok(celsius)};
    std::println("{}", kelvin);
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
