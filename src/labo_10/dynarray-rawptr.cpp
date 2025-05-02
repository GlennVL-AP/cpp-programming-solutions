export module dynarray:rawptr;

import cpprog;
import std;

namespace rawptr {

export template <typename T>
class DynamicArray // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
{
public:
    DynamicArray() = default;

    explicit DynamicArray(int capacity) : capacity_{capacity}, data_{make_array(capacity_)} {}

    ~DynamicArray() { delete[] data_; }

    DynamicArray(DynamicArray const& other) : capacity_{other.capacity_}, data_{make_array(capacity_)}
    {
        std::copy_n(other.begin(), other.size(), begin());
    }

    DynamicArray(DynamicArray&& other) noexcept { swap(*this, other); }

    // the special member function nolint is required because clang-tidy does not recognize this covers both copy and move
    DynamicArray& operator=(DynamicArray rhs) noexcept
    {
        swap(*this, rhs);
        return *this;
    }

    // to make clang-tidy happy the following code would be required instead of by-value copy, but is not idiomatic
    // DynamicArray& operator=(DynamicArray const& rhs)
    // {
    //     auto copy{rhs};
    //     swap(*this, copy);
    //     return *this;
    // }
    // DynamicArray& operator=(DynamicArray&& rhs) noexcept
    // {
    //     swap(*this, rhs);
    //     return *this;
    // }

    [[nodiscard]] int size() const { return capacity_; }

    [[nodiscard]] T const& operator[](int index) const
    {
        cpprog::expect([&, this] { return (0 <= index) && (index < size()); }, "0 <= index < size()");
        return *std::next(begin(), index); // or data_[index] with a suppress for pointer arithmetic
    }

    [[nodiscard]] T& operator[](int index)
    {
        cpprog::expect([&, this] { return (0 <= index) && (index < size()); }, "0 <= index < size()");
        return *std::next(begin(), index); // or data_[index] with a suppress for pointer arithmetic
    }

    [[nodiscard]] T* begin() const { return data_; } // or &data_[0] with a suppress for pointer arithmetic
    [[nodiscard]] T* end() const { return std::next(begin(), size()); } // or &data_[capacity_] with a suppress

private:
    int capacity_{};

    // NOLINTBEGIN(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)

    T* data_{};

    [[nodiscard]] static T* make_array(int capacity)
    {
        cpprog::expect([&] { return 0 <= capacity; }, "capacity can't be negative");
        return (capacity == 0) ? nullptr : new T[static_cast<std::size_t>(capacity)]{};
    }

    // NOLINTEND(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)

    friend void swap(DynamicArray& first, DynamicArray& second) noexcept
    {
        using std::swap;
        swap(first.capacity_, second.capacity_);
        swap(first.data_, second.data_);
    }
};

export template <typename T>
[[nodiscard]] bool operator==(DynamicArray<T> const& lhs, DynamicArray<T> const& rhs)
{
    return std::ranges::equal(lhs, rhs);
}

export template <typename T>
[[nodiscard]] bool operator!=(DynamicArray<T> const& lhs, DynamicArray<T> const& rhs)
{
    return !(lhs == rhs);
}

export template <typename T>
DynamicArray<T> operator+(DynamicArray<T> const& lhs, DynamicArray<T> const& rhs)
{
    DynamicArray<T> result{lhs.size() + rhs.size()};
    std::copy_n(lhs.begin(), lhs.size(), result.begin());
    // using std::next prevents needing access to lhs.data_ which is private
    std::copy_n(rhs.begin(), rhs.size(), std::next(result.begin(), lhs.size()));
    return result;
}

export template <typename T>
DynamicArray<T>& operator+=(DynamicArray<T>& lhs, DynamicArray<T> const& rhs)
{
    auto tmp = lhs + rhs;
    swap(lhs, tmp);
    return lhs;
}

} // namespace rawptr
