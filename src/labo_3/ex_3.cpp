import cpprog;
import std;

namespace {

constexpr double kelvin_offset{273.15};

double ctok(double celsius)
{
    cpprog::expect([&] { return -kelvin_offset <= celsius; }, "Temperature can't be below absolute zero!");
    return celsius + kelvin_offset;
}

double ktoc(double kelvin)
{
    cpprog::expect([&] { return 0 <= kelvin; }, "Temperature can't be below absolute zero!");
    return kelvin - kelvin_offset;
}

} // namespace

int main()
try
{
    double celsius{0.0};
    std::cin >> celsius;
    double const kelvin{ctok(celsius)};
    std::println("{}K = {}C", kelvin, ktoc(kelvin));
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
