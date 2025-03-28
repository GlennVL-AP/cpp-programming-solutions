export module fibonacci;

import cpprog;
import std;

namespace {

int fib_loop_impl(int number)
{
    if (number < 2) { return number; }

    int result{0};
    for (int first{0}, second{1}, i{2}; i <= number; ++i)
    {
        result = first + second;
        first = second;
        second = result;
    }
    return result;
}

} // namespace

export auto fib_loop = [cache = std::unordered_map<int, int>{}](int number) mutable {
    cpprog::expect([&] { return number >= 0; }, "Number must be positive!");
    if (!cache.contains(number)) { cache[number] = fib_loop_impl(number); }
    return cache[number];
};

export auto fib_recursive = [cache = std::unordered_map<int, int>{{0, 0},{1, 1}}](int number) mutable {
    cpprog::expect([&] { return number >= 0; }, "Number must be positive!");
    auto fib_rec_impl = [&cache](auto&& self, int number) -> int {
        if (!cache.contains(number)) { cache[number] = self(self, number - 1) + self(self, number - 2); }
        return cache[number];
    };
    return fib_rec_impl(fib_rec_impl, number);
};
