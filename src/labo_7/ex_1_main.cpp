import containsnumber;
import std;

int main()
try
{
    std::vector<int> const numbers{1, 2, 1, 3, 1, 4, 1, 5};

    if (contains_number(numbers, 4))
    {
        std::println("Gevonden!");
    }
    else
    {
        std::println("Niet gevonden!");
    }
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
