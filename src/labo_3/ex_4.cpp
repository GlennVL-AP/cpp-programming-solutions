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

    std::unordered_map<int, int> to_guess_not_bull{};
    std::vector<int> guess_not_bull{};

    for (auto const& [number_to_guess, guessed_number] : std::views::zip(to_guess, guess))
    {
        if (number_to_guess == guessed_number)
        {
            ++result.bulls;
        }
        else
        {
            ++to_guess_not_bull[number_to_guess];
            guess_not_bull.push_back(guessed_number);
        }
    }

    for (auto const& guessed_number : guess_not_bull)
    {
        if (0 < to_guess_not_bull[guessed_number])
        {
            ++result.cows;
            --to_guess_not_bull[guessed_number];
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
        auto const result = bulls_and_cows(to_guess, guess);
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
