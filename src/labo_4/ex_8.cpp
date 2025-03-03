import std;

int main()
try
{
    using namespace std::chrono;
    using namespace std::literals::chrono_literals;

    std::println("UTC time: {}", system_clock::now());

    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    std::println("Valid day: {}", 2025y/March/3d);
    std::println("Invalid day: {}", 2025y/February/29d);

    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    return 0;
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
