import std;

int main()
try
{
    std::unordered_map<std::string, int> word_counts{};

    std::println("Geef een reeks woorden:");
    for (std::string word{}; std::cin >> word;)
    {
        if (word_counts.contains(word))
        {
            ++word_counts[word];
        }
        else
        {
            word_counts[word] = 1;
        }
    }

    for (auto const& [word, count] : word_counts)
    {
        std::println("{}: {}", word, count);
    }

    return 0;
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
