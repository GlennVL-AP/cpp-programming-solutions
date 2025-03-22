import cpprog;
import std;

namespace {

double ctok(double celsius)
{
    static constexpr double kelvin_offset{273.15};
    cpprog::expect([&] { return -kelvin_offset <= celsius; }, "Temperature can't be below absolute zero!");
    return celsius + kelvin_offset;
}

} // namespace

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
