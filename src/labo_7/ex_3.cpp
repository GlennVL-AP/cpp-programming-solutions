import std;

namespace {

std::vector<int> read_numbers()
{
    std::vector<int> numbers{};
    std::println("Geef een aantal getallen:");
    for (int number{}; std::cin >> number;) { numbers.push_back(number); }
    return numbers;
}

std::vector<int> transform_numbers(std::vector<int> const& numbers)
{
    auto result = numbers | std::views::filter([](int number) { return (number % 3) == 0; })
                          | std::views::transform([](int number) { return number * number; })
                          | std::ranges::to<std::vector>();

    std::ranges::sort(result);

    return result;
}

} // namespace

int main()
try
{
    for (auto const& number : transform_numbers(read_numbers())) { std::print("{},", number); }
    std::println();
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
