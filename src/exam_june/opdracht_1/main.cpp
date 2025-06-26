import std;

int main()
try
{
    std::println("Geef 3 getallen:");
    int first{};
    int second{};
    int third{};
    std::cin >> first >> second >> third;
    std::println("Het kleinste getal is: {}", std::min({first, second, third}));
    std::println("Het grootst getal is: {}", std::max({first, second, third}));
}
catch (std::exception const& e)
{
    std::cerr << e.what() << "\n";
    return 1;
}
