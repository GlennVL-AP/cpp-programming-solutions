import std;

int main() // NOLINT(bugprone-exception-escape)
{
    static constexpr int months_per_year{12};

    std::print("Geef je voornaam en leeftijd: ");

    std::string first_name{};
    int age{};
    std::cin >> first_name >> age;

    std::println("Dag {}, je bent {} maanden oud.", first_name, age * months_per_year);
}
