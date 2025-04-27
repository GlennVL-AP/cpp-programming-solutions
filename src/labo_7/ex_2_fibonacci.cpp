export module fibonacci;

import cpprog;
import std;

namespace {

std::int64_t fib_loop_impl(int number)
{
    if (number < 2) { return number; }

    std::int64_t result{0};
    for (std::int64_t first{0}, second{1}, i{2}; i <= number; ++i)
    {
        result = first + second;
        first = second;
        second = result;
    }
    return result;
}

} // namespace

export auto fib_loop = [cache = std::unordered_map<int, std::int64_t>{}](int number) mutable {
    cpprog::expect([&] { return number >= 0; }, "Number must be positive!");
    if (!cache.contains(number)) { cache[number] = fib_loop_impl(number); }
    return cache[number];
};

export auto fib_recursive = [cache = std::unordered_map<std::int64_t, std::int64_t>{{0, 0},{1, 1}}](int number) mutable {
    cpprog::expect([&] { return number >= 0; }, "Number must be positive!");
    auto fib_rec_impl = [&cache](auto&& self, std::int64_t current_number) -> std::int64_t {
        if (!cache.contains(current_number))
        {
            cache[current_number] = self(self, current_number - 2) + self(self, current_number - 1);
        }
        return cache[current_number];
    };
    return fib_rec_impl(fib_rec_impl, number);
};
