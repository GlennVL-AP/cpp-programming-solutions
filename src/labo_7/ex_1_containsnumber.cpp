export module containsnumber;

import std;

export bool contains_number(std::vector<int> const& numbers, int value)
{
    return std::ranges::any_of(numbers, [&](int number) { return number == value; });
}
