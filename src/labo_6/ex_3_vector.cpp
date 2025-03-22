export module vector3d;

import std;
import cpprog;

export class X
{
public:
    constexpr X() = default;
    constexpr explicit X(double value) : value_{value} {}

    [[nodiscard]] constexpr double get() const { return value_; }
    [[nodiscard]] constexpr double& get() { return value_; }

    constexpr X& operator=(double value) { value_ = value; return *this; }

    constexpr auto operator<=>(X const&) const = default;

private:
    double value_{};
};

export class Y
{
public:
    constexpr Y() = default;
    constexpr explicit Y(double value) : value_{value} {}

    [[nodiscard]] constexpr double get() const { return value_; }
    [[nodiscard]] constexpr double& get() { return value_; }

    constexpr Y& operator=(double value) { value_ = value; return *this; }

    constexpr auto operator<=>(Y const&) const = default;

private:
    double value_{};
};

export class Z
{
public:
    constexpr Z() = default;
    constexpr explicit Z(double value) : value_{value} {}

    [[nodiscard]] constexpr double get() const { return value_; }
    [[nodiscard]] constexpr double& get() { return value_; }

    constexpr Z& operator=(double value) { value_ = value; return *this; }

    constexpr auto operator<=>(Z const&) const = default;

private:
    double value_{};
};

export class Vector3D
{
public:
    constexpr Vector3D() = default;
    constexpr Vector3D(X x_value, Y y_value, Z z_value) : x_{x_value}, y_{y_value}, z_{z_value} {}

    [[nodiscard]] constexpr X const& x() const { return x_; }
    [[nodiscard]] constexpr X& x() { return x_; }
    [[nodiscard]] constexpr Y const& y() const { return y_; }
    [[nodiscard]] constexpr Y& y() { return y_; }
    [[nodiscard]] constexpr Z const& z() const { return z_; }
    [[nodiscard]] constexpr Z& z() { return z_; }

    [[nodiscard]] constexpr double operator[](int index) const
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

    [[nodiscard]] constexpr double& operator[](int index)
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
    X x_;
    Y y_;
    Z z_;
};

export [[nodiscard]] constexpr bool operator==(Vector3D const& lhs, Vector3D const& rhs)
{
    return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y()) && (lhs.z() == rhs.z());
}

export [[nodiscard]] constexpr bool operator!=(Vector3D const& lhs, Vector3D const& rhs)
{
    return !(lhs == rhs);
}

export constexpr Vector3D& operator+=(Vector3D& lhs, Vector3D const& rhs)
{
    lhs.x().get() += rhs.x().get();
    lhs.y().get() += rhs.y().get();
    lhs.z().get() += rhs.y().get();

    return lhs;
}

export constexpr Vector3D operator+(Vector3D const& lhs, Vector3D const& rhs)
{
    Vector3D result{lhs};
    result += rhs;
    return result;
}

export constexpr Vector3D operator-(Vector3D const& vec)
{
    return {X{-(vec.x().get())}, Y{-(vec.y().get())}, Z{-(vec.z().get())}};
}

export constexpr Vector3D& operator-=(Vector3D& lhs, Vector3D const& rhs)
{
    return lhs += -rhs;
}

export constexpr Vector3D operator-(Vector3D const& lhs, Vector3D const& rhs)
{
    return lhs + -rhs;
}

export constexpr Vector3D& operator*=(Vector3D& lhs, double scalar)
{
    lhs.x().get() *= scalar;
    lhs.y().get() *= scalar;
    lhs.z().get() *= scalar;

    return lhs;
}

export constexpr Vector3D operator*(Vector3D const& lhs, double scalar)
{
    Vector3D result{lhs};
    result *= scalar;
    return result;
}
