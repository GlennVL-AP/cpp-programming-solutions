import fibonacci;
import std;

int main()
try
{
    auto const result = std::views::iota(1)
                      | std::views::take(75)
                      | std::views::drop(24)
                      | std::views::transform([&](int value) { return fib_recursive(value); })
                      | std::ranges::to<std::vector>();

    for (auto const& number : result)
    {
        std::print("{},", number);
    }
    std::println();
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
