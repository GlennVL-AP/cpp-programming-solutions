import matrix;
import std;

int main()
try
{
    static constexpr linalg::Matrix<double, 3, 3> matrix{
        1.0, 3.0, 6.0,
        2.0, 5.0, 8.0,
        4.0, 7.0, 9.0
    };

    std::println("determinant = {:.2f}", linalg::determinant(matrix));

    return 0;
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}
