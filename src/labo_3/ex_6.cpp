// NOLINTBEGIN(readability-identifier-length)

import cpprog;
import std;

struct Roots
{
    double root_1{};
    double root_2{};
};

std::optional<Roots> solve_quadratic_equation(double a, double b, double c)
{
    cpprog::expect([&] { return a != 0.0; }, "expect quadratic equation");

    double const to_sqrt{(b * b) - (4 * a * c)};
    if (to_sqrt < 0.0) { return {}; }

    double const sqrted{std::sqrt(to_sqrt)};
    return Roots{.root_1 = (-b + sqrted) / (2 * a), .root_2 = (-b - sqrted) / (2 * a)};
}

int main()
try
{
    std::print("Geeft a, b en c: ");
    double a{};
    double b{};
    double c{};
    std::cin >> a >> b >> c;

    if (a == 0.0) { std::println("Vergelijking moet van de tweede graad zijn (a != 0)"); }
    else if (auto result = solve_quadratic_equation(a, b, c))
    {
        std::println("Nulpunten: {} en {}", result->root_1, result->root_2);
    }
    else { std::println("Geen nulpunten!"); }

    return 0;
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}

// NOLINTEND(readability-identifier-length)
