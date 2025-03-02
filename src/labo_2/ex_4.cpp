import std;

int main() // NOLINT(bugprone-exception-escape)
{
    std::print("Geef een geheel getal: ");

    int number{};
    std::cin >> number;

    if (number % 2 == 0)
    {
        std::println("{} is even", number);
    }
    else
    {
        std::println("{} is oneven", number);
    }
}
