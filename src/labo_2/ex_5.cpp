import std;

int main() // NOLINT(bugprone-exception-escape)
{
    std::print("Geef een operator (+, -, *, /, %) en twee getallen (vb + 1 2): ");

    char action{};
    int first_number{};
    int second_number{};
    std::cin >> action >> first_number >> second_number;

    switch (action)
    {
    case '+': std::println("{} {} {} = {}", first_number, action, second_number, first_number + second_number); break;
    case '-': std::println("{} {} {} = {}", first_number, action, second_number, first_number - second_number); break;
    case '*': std::println("{} {} {} = {}", first_number, action, second_number, first_number * second_number); break;
    case '/': std::println("{} {} {} = {}", first_number, action, second_number, first_number / second_number); break;
    case '%': std::println("{} {} {} = {}", first_number, action, second_number, first_number % second_number); break;
    default: std::println("Ongeldige operator {}", action); break;
    }
}
