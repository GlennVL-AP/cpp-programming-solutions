import std;

int main() // NOLINT(bugprone-exception-escape)
{
    static constexpr int min_number{0};
    static constexpr int max_number{4};

    std::print("Geef een getal van 0 tem 4: ");
    int number{};
    std::cin >> number;

    if ((min_number <= number) && (number <= max_number))
    {
        std::vector<std::string> const numbers{"nul", "een", "twee", "drie", "vier"};
        std::println("{} in tekst is {}", number, numbers[static_cast<std::size_t>(number)]);
    }
    else
    {
        std::println("Kan het getal niet converteren!");
    }
}
