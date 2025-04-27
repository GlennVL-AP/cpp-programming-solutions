export module circularbuffer;

import cpprog;
import std;

export
template <typename T, int N>
requires (0 < N)
class CircularBuffer
{
public:
    [[nodiscard]] constexpr bool is_empty() const
    {
        return back_ == front_;
    }

    [[nodiscard]] constexpr bool is_full() const
    {
        return next_index(back_) == front_;
    }

    constexpr void push_back(T const& value)
    {
        cpprog::expect([this]{ return !is_full(); }, "cannot push to full buffer");

        data_[static_cast<std::size_t>(back_)] = value;
        back_ = next_index(back_);
    }

    constexpr T pop_front()
    {
        cpprog::expect([this]{ return !is_empty(); }, "cannot pop from empty buffer");

        auto const value = data_[static_cast<std::size_t>(front_)];
        front_ = next_index(front_);
        return value;
    }

private:
    std::array<T, static_cast<std::size_t>(N + 1)> data_{};
    int front_{};
    int back_{};

    static constexpr int next_index(int index)
    {
        if (++index > N) { index = 0; }
        return index;
    }
};
