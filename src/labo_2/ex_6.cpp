import std;

int main() // NOLINT(bugprone-exception-escape)
{
    std::println("Geeft telkens twee getallen, type ! om te stoppen.");

    for (int first{}, second{}; std::cin >> first >> second;)
    {
        std::println("{} is het kleinste", std::min(first, second));
    }
}
