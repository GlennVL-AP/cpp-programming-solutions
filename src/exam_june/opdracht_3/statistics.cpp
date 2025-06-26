export module statistics;

import cpprog;
import std;

export class Statistics
{
public:
    void add(int number)
    {
        numbers_.push_back(number);
    }

    [[nodiscard]] int sum() const
    {
        cpprog::expect([this]{ return !numbers_.empty(); }, "list must not be empty");
        return std::accumulate(std::begin(numbers_), std::end(numbers_), 0);
    }

    [[nodiscard]] double average() const
    {
        cpprog::expect([this]{ return !numbers_.empty(); }, "list must not be empty");
        return static_cast<double>(sum()) / static_cast<double>(numbers_.size());
    }

    [[nodiscard]] int max() const
    {
        cpprog::expect([this]{ return !numbers_.empty(); }, "list must not be empty");
        return std::ranges::max(numbers_);
    }

private:
    std::vector<int> numbers_;
};
