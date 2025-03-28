import std;

namespace {

std::vector<double> read_numbers()
{
    std::vector<double> numbers{};
    std::println("Geef een aantal getallen:");
    for (double number{}; std::cin >> number;) { numbers.push_back(number); }
    return numbers;
}

double calculate_average(std::vector<double> const& numbers)
{
    auto const sum = std::accumulate(std::begin(numbers), std::end(numbers), 0.0, [](double sum, double value) {
        return sum + value;
    });

    auto const count = std::distance(std::begin(numbers), std::end(numbers));

    return sum / static_cast<double>(count);
}

} // namespace

int main()
try
{
    std::println("The average is {}", calculate_average(read_numbers()));
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
