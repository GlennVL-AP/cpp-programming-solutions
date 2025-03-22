import std;
import shapes;

namespace {

double area(shapes::Shape const& shape)
{
    return shape.area();
}

double circumference(shapes::Shape const& shape)
{
    return shape.circumference();
}

} // namespace

int main()
try
{
    shapes::Circle const circle{shapes::Radius{1.0}};
    shapes::Square const square{shapes::Side{1.0}};
    shapes::Rectangle const rectangle{shapes::Length{1.0}, shapes::Width{1.0}};

    std::println("circle area = {}", area(circle));
    std::println("square area = {}", area(square));
    std::println("rectangle area = {}", area(rectangle));
    std::println("circle circumference = {}", circumference(circle));
    std::println("square circumference = {}", circumference(square));
    std::println("rectangle circumference = {}", circumference(rectangle));
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
