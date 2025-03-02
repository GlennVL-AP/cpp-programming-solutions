import std;

double ctok(double celsius)
{
    static constexpr double kelvin_offset{273.15};
    double const kelvin{celsius + kelvin_offset};
    return kelvin;
}

int main()
try
{
    double celsius{0.0};
    std::cin >> celsius;
    double kelvin = ctok(celsius);
    std::println("{}", kelvin);
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
