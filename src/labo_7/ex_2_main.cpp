import fibonacci;
import std;

int main()
try
{
    std::print("Geef een getal: ");
    int number{};
    std::cin >> number;
    std::println("fibonacci({}) = {}", number, fib_recursive(number));
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
