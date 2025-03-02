import cpprog;
import std;

constexpr double kelvin_offset{273.15};

double ctok(double celsius)
{
    cpprog::expect([&] { return -kelvin_offset <= celsius; }, "Temperature can't be below absolute zero!");
    double const kelvin{celsius + kelvin_offset};
    return kelvin;
}

double ktoc(double kelvin)
{
    cpprog::expect([&] { return 0 <= kelvin; }, "Temperature can't be below absolute zero!");
    double const celsius{kelvin - kelvin_offset};
    return celsius;
}

int main()
try
{
    double celsius{0.0};
    std::cin >> celsius;
    double kelvin = ctok(celsius);
    std::println("{}K = {}C", kelvin, ktoc(kelvin));
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
