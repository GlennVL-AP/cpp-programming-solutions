import cpprog;
import std;

struct BullsCows
{
    int bulls{};
    int cows{};
};

BullsCows bulls_and_cows(std::vector<int> const& to_guess, std::vector<int> const& guess)
{
    cpprog::expect([&] { return to_guess.size() == guess.size(); }, "guess and to_guess must be same size");

    BullsCows result{};

    for (std::size_t i{0}; i < guess.size(); ++i)
    {
        if (guess[i] == to_guess[i])
        {
            ++result.bulls;
        }
        else
        {
            for (std::size_t j{0}; j < guess.size(); ++j)
            {
                if (guess[i] == to_guess[j])
                {
                    ++result.cows;
                }
            }
        }
    }

    return result;
}

int main()
try
{
    std::println("Bull and Cows.");

    std::vector<int> const to_guess{3, 6, 4, 8};

    for (;;)
    {
        std::print("Geeft 4 getallen: ");
        std::vector<int> guess{0, 0, 0, 0};
        std::cin >> guess[0] >> guess[1] >> guess[2] >> guess[3];
        auto result = bulls_and_cows(to_guess, guess);
        std::println("{} bulls, {} cows", result.bulls, result.cows);
        if (result.bulls == std::ssize(to_guess)) { break; }
    }

    return 0;
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
