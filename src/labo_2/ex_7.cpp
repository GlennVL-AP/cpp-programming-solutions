import std;

int main() // NOLINT(bugprone-exception-escape)
{
    std::vector<double> numbers{};

    std::println("Geef een reeks komma-getallen: ");
    for (double number{}; std::cin >> number;)
    {
        numbers.push_back(number);
    }

    double sum{0.0};
    for (double const& number : numbers)
    {
        sum += number;
    }
    std::println("De som is {}", sum);
}
