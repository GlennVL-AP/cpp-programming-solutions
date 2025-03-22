export module shapes;

import std;

namespace shapes {

constexpr double two{2.0};
constexpr double four{4.0};

export class Shape
{
public:
    Shape() = default;
    virtual ~Shape() = default;

    Shape(Shape const&) = delete;
    Shape& operator=(Shape const&) = delete;
    Shape(Shape&&) = delete;
    Shape& operator=(Shape&&) = delete;

    [[nodiscard]] virtual double area() const = 0;
    [[nodiscard]] virtual double circumference() const = 0;
};

export class Radius
{
public:
    constexpr Radius() = default;
    constexpr explicit Radius(double value) : value_{value} {}

    [[nodiscard]] constexpr double get() const { return value_; }
    [[nodiscard]] constexpr double& get() { return value_; }

private:
    double value_{};
};

export class Circle : public Shape
{
public:
    constexpr Circle() = default;
    explicit Circle(Radius radius) : radius_{radius} {}

    [[nodiscard]] Radius const& radius() const { return radius_; }

    [[nodiscard]] double area() const override { return std::numbers::pi * radius_.get() * radius_.get(); }
    [[nodiscard]] double circumference() const override { return two * std::numbers::pi * radius_.get(); }

private:
    Radius radius_;
};

export class Side
{
public:
    constexpr Side() = default;
    constexpr explicit Side(double value) : value_{value} {}

    [[nodiscard]] constexpr double get() const { return value_; }
    [[nodiscard]] constexpr double& get() { return value_; }

private:
    double value_{};
};

export class Square : public Shape
{
public:
    explicit Square(Side side) : side_{side} {}

    [[nodiscard]] Side const& side() const { return side_; }

    [[nodiscard]] double area() const override { return side_.get() * side_.get(); }
    [[nodiscard]] double circumference() const override { return four * side_.get(); }

private:
    Side side_;
};

export class Length
{
public:
    constexpr Length() = default;
    constexpr explicit Length(double value) : value_{value} {}

    [[nodiscard]] constexpr double get() const { return value_; }
    [[nodiscard]] constexpr double& get() { return value_; }

private:
    double value_{};
};

export class Width
{
public:
    constexpr Width() = default;
    constexpr explicit Width(double value) : value_{value} {}

    [[nodiscard]] constexpr double get() const { return value_; }
    [[nodiscard]] constexpr double& get() { return value_; }

private:
    double value_{};
};

export class Rectangle : public Shape
{
public:
    explicit Rectangle(Length length, Width width) : length_{length}, width_{width} {}

    [[nodiscard]] Length const& length() const { return length_; }
    [[nodiscard]] Width const& width() const { return width_; }

    [[nodiscard]] double area() const override { return length_.get() * width_.get(); }
    [[nodiscard]] double circumference() const override { return two * (length_.get() + width_.get()); }

private:
    Length length_;
    Width width_;
};

} // namespace shapes
