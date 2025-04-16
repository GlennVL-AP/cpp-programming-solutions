export module matrix;

import std;
import cpprog;

namespace linalg {

template <typename T>
concept Arithmetic = requires(T first, T second) {
    { -first } -> std::same_as<T>;
    { first + second } -> std::same_as<T>;
    { first - second } -> std::same_as<T>;
    { first * second } -> std::same_as<T>;
    { first == second } -> std::convertible_to<bool>;
};

template <typename T>
concept NumberLike = std::default_initializable<T> && std::constructible_from<T, int> && std::swappable<T> && Arithmetic<T>;

export template <NumberLike T, int M, int N>
requires (0 < M) && (0 < N)
class Matrix
{
    using ValueType = T;

public:
    constexpr Matrix() = default;

    constexpr explicit Matrix(T value)
    {
        std::ranges::fill(data_, value);
    }

    constexpr Matrix(std::initializer_list<ValueType> values)
    {
        cpprog::expect([&]{ return values.size() == M*N; }, "requires MxN items");

        std::ranges::copy(values, std::begin(data_));
    }

    [[nodiscard]] constexpr ValueType operator[](int i_index, int j_index) const
    {
        cpprog::expect([&]{ return (0 <= i_index) && (i_index < M); }, "0 <= i < M");
        cpprog::expect([&]{ return (0 <= j_index) && (j_index < N); }, "0 <= j < N");

        return data_[static_cast<std::size_t>((i_index * N) + j_index)];
    }

    [[nodiscard]] constexpr ValueType& operator[](int i_index, int j_index)
    {
        cpprog::expect([&]{ return (0 <= i_index) && (i_index < M); }, "0 <= i < M");
        cpprog::expect([&]{ return (0 <= j_index) && (j_index < N); }, "0 <= j < N");

        return data_[static_cast<std::size_t>((i_index * N) + j_index)];
    }

private:
    std::array<ValueType, static_cast<std::size_t>(M*N)> data_{};
};

export template <typename T, int M, int N>
[[nodiscard]] constexpr bool operator==(Matrix<T, M, N> const& lhs, Matrix<T, M, N> const& rhs)
{
    for (int i{0}; i < M; ++i)
    {
        for (int j{0}; j < N; ++j)
        {
            if (lhs[i,j] != rhs[i,j])
            {
                return false;
            }
        }
    }

    return true;
}

export template <typename T, int M, int N>
[[nodiscard]] constexpr bool operator!=(Matrix<T, M, N> const& lhs, Matrix<T, M, N> const& rhs)
{
    return !(lhs == rhs);
}

export template <typename T, int M, int N>
constexpr Matrix<T, M, N>& operator+=(Matrix<T, M, N>& lhs, Matrix<T, M, N> const& rhs)
{
    for (int i{0}; i < M; ++i)
    {
        for (int j{0}; j < N; ++j)
        {
            lhs[i,j] += rhs[i,j];
        }
    }

    return lhs;
}

export template <typename T, int M, int N>
[[nodiscard]] constexpr Matrix<T, M, N> operator+(Matrix<T, M, N> const& lhs, Matrix<T, M, N> const& rhs)
{
    auto result{lhs};
    result += rhs;
    return result;
}

export template <typename T, int M, int N>
[[nodiscard]] constexpr Matrix<T, M, N> operator-(Matrix<T, M, N> const& matrix)
{
    auto result{matrix};

    for (int i{0}; i < M; ++i)
    {
        for (int j{0}; j < N; ++j)
        {
            result[i,j] = -result[i,j];
        }
    }

    return result;
}

export template <typename T, int M, int N>
constexpr Matrix<T, M, N>& operator-=(Matrix<T, M, N>& lhs, Matrix<T, M, N> const& rhs)
{
    return lhs += -rhs;
}

export template <typename T, int M, int N>
[[nodiscard]] constexpr Matrix<T, M, N> operator-(Matrix<T, M, N> const& lhs, Matrix<T, M, N> const& rhs)
{
    return lhs + -rhs;
}

export template <typename T, int M, int N>
constexpr Matrix<T, M, N>& operator*=(Matrix<T, M, N>& lhs, T scalar)
{
    for (int i{0}; i < M; ++i)
    {
        for (int j{0}; j < N; ++j)
        {
            lhs[i,j] *= scalar;
        }
    }

    return lhs;
}

export template <typename T, int M, int N>
[[nodiscard]] constexpr Matrix<T, M, N> operator*(Matrix<T, M, N> const& lhs, T scalar)
{
    auto result{lhs};
    result *= scalar;
    return result;
}

export template <typename T, int M, int N, int P>
[[nodiscard]] constexpr Matrix<T, M, P> operator*(Matrix<T, M, N> const& lhs, Matrix<T, N, P> const& rhs)
{
    Matrix<T, M, P> result{};

    for (int i{0}; i < M; ++i)
    {
        for (int j{0}; j < P; ++j)
        {
            for (int k{0}; k < N; ++k)
            {
                result[i,j] += lhs[i,k] * rhs[k,j];
            }
        }
    }

    return result;
}

export template <typename T, int M>
[[nodiscard]] constexpr T determinant(Matrix<T, M, M> matrix)
{
    auto abs = [](auto const& value){ return value < 0 ? -value : value; };

    T result{1};

    for (int i{0}; i < M; ++i)
    {
        auto pivot{i};
        for (int j{i+1}; j < M; ++j)
        {
            if (abs(matrix[pivot,i]) < abs(matrix[j,i]))
            {
                pivot = j;
            }
        }
        if (pivot != i)
        {
            for (int j{0}; j < M; ++j)
            {
                using std::swap;
                swap(matrix[i,j], matrix[pivot,j]);
            }
            result = -result;
        }
        result *= matrix[i,i];
        for (int j{i+1}; j < M; ++j)
        {
            auto const factor = matrix[j,i] / matrix[i,i];
            for (int k{i+1}; k < M; ++k)
            {
                matrix[j,k] -= factor * matrix[i,k];
            }
        }
    }

    return result;
}

export template <typename T, int M, int N>
[[nodiscard]] constexpr Matrix<T, N, M> transpose(Matrix<T, M, N> const& matrix)
{
    Matrix<T, N, M> result{};

    for (int i{0}; i < N; ++i)
    {
        for (int j{0}; j < M; ++j)
        {
            result[i,j] = matrix[j,i];
        }
    }

    return result;
}

} // namespace linalg
