export module vector3d;

import std;
import cpprog;

template <typename T>
concept NumericType = std::is_arithmetic_v<T>;

export template <NumericType T>
class X
{
    using ValueType = T;

public:
    constexpr X() = default;
    constexpr explicit X(ValueType value) : value_{value} {}

    [[nodiscard]] constexpr ValueType get() const { return value_; }
    [[nodiscard]] constexpr ValueType& get() { return value_; }

    constexpr X& operator=(ValueType value) { value_ = value; return *this; }

    constexpr auto operator<=>(X const&) const = default;

private:
    ValueType value_{};
};

export template <NumericType T>
class Y
{
    using ValueType = T;

public:
    constexpr Y() = default;
    constexpr explicit Y(ValueType value) : value_{value} {}

    [[nodiscard]] constexpr ValueType get() const { return value_; }
    [[nodiscard]] constexpr ValueType& get() { return value_; }

    constexpr Y& operator=(ValueType value) { value_ = value; return *this; }

    constexpr auto operator<=>(Y const&) const = default;

private:
    ValueType value_{};
};

export template <NumericType T>
class Z
{
    using ValueType = T;

public:
    constexpr Z() = default;
    constexpr explicit Z(ValueType value) : value_{value} {}

    [[nodiscard]] constexpr ValueType get() const { return value_; }
    [[nodiscard]] constexpr ValueType& get() { return value_; }

    constexpr Z& operator=(ValueType value) { value_ = value; return *this; }

    constexpr auto operator<=>(Z const&) const = default;

private:
    ValueType value_{};
};

export template <NumericType T>
class Vector3D
{
    using ValueType = T;

public:
    constexpr Vector3D() = default;
    constexpr Vector3D(X<ValueType> x_value, Y<ValueType> y_value, Z<ValueType> z_value)
        : x_{x_value}, y_{y_value}, z_{z_value} {}

    [[nodiscard]] constexpr X<ValueType> const& x() const { return x_; }
    [[nodiscard]] constexpr X<ValueType>& x() { return x_; }
    [[nodiscard]] constexpr Y<ValueType> const& y() const { return y_; }
    [[nodiscard]] constexpr Y<ValueType>& y() { return y_; }
    [[nodiscard]] constexpr Z<ValueType> const& z() const { return z_; }
    [[nodiscard]] constexpr Z<ValueType>& z() { return z_; }

    [[nodiscard]] constexpr ValueType operator[](int index) const
    {
        cpprog::expect([&]{ return (0 <= index) && (index <= 2); }, "index must be 0, 1, 2");

        switch (index)
        {
        case 0: return x_.get(); break;
        case 1: return y_.get(); break;
        case 2: return z_.get(); break;
        default: std::unreachable(); break;
        }
    }

    [[nodiscard]] constexpr ValueType& operator[](int index)
    {
        cpprog::expect([&]{ return (0 <= index) && (index <= 2); }, "index must be 0, 1, 2");

        switch (index)
        {
        case 0: return x_.get(); break;
        case 1: return y_.get(); break;
        case 2: return z_.get(); break;
        default: std::unreachable(); break;
        }
    }

private:
    X<ValueType> x_;
    Y<ValueType> y_;
    Z<ValueType> z_;
};

export template <NumericType T>
[[nodiscard]] constexpr bool operator==(Vector3D<T> const& lhs, Vector3D<T> const& rhs)
{
    return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y()) && (lhs.z() == rhs.z());
}

export template <NumericType T>
[[nodiscard]] constexpr bool operator!=(Vector3D<T> const& lhs, Vector3D<T> const& rhs)
{
    return !(lhs == rhs);
}

export template <NumericType T>
constexpr Vector3D<T>& operator+=(Vector3D<T>& lhs, Vector3D<T> const& rhs)
{
    lhs.x().get() += rhs.x().get();
    lhs.y().get() += rhs.y().get();
    lhs.z().get() += rhs.z().get();

    return lhs;
}

export template <NumericType T>
constexpr Vector3D<T> operator+(Vector3D<T> const& lhs, Vector3D<T> const& rhs)
{
    Vector3D<T> result{lhs};
    result += rhs;
    return result;
}

export template <NumericType T>
constexpr Vector3D<T> operator-(Vector3D<T> const& vec)
{
    return {X{-(vec.x().get())}, Y{-(vec.y().get())}, Z{-(vec.z().get())}};
}

export template <NumericType T>
constexpr Vector3D<T>& operator-=(Vector3D<T>& lhs, Vector3D<T> const& rhs)
{
    return lhs += -rhs;
}

export template <NumericType T>
constexpr Vector3D<T> operator-(Vector3D<T> const& lhs, Vector3D<T> const& rhs)
{
    return lhs + -rhs;
}

export template <NumericType T>
constexpr Vector3D<T>& operator*=(Vector3D<T>& lhs, T scalar)
{
    lhs.x().get() *= scalar;
    lhs.y().get() *= scalar;
    lhs.z().get() *= scalar;

    return lhs;
}

export template <NumericType T>
constexpr Vector3D<T> operator*(Vector3D<T> const& lhs, T scalar)
{
    Vector3D<T> result{lhs};
    result *= scalar;
    return result;
}
