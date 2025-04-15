// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

import vector3d;
import std;

int main()
try
{
    linalg::Vector3D vec_1{linalg::X{1.1}, linalg::Y{2.2}, linalg::Z{3.3}};
    linalg::Vector3D vec_2{linalg::X{3.3}, linalg::Y{1.1}, linalg::Z{2.2}};
    linalg::Vector3D vec_3{vec_1 + vec_2};
    linalg::Vector3D vec_4{vec_1 - vec_2};
    linalg::Vector3D vec_5{vec_4 * std::numbers::pi};

    vec_1 += vec_2;
    vec_2 -= vec_3;
    vec_3 *= std::numbers::pi;
    vec_4[0] = std::numbers::e;
    vec_5[2] = std::numbers::inv_pi;

    std::println("vec_1 = {}, {}, {}", vec_1[0], vec_1[1], vec_1[2]);
    std::println("vec_2 = {}, {}, {}", vec_2[0], vec_2[1], vec_2[2]);
    std::println("vec_3 = {}, {}, {}", vec_3[0], vec_3[1], vec_3[2]);
    std::println("vec_4 = {}, {}, {}", vec_4[0], vec_4[1], vec_4[2]);
    std::println("vec_5 = {}, {}, {}", vec_5[0], vec_5[1], vec_5[2]);
    std::println("vec_3 != vec_4? {}", vec_3 != vec_4);

    return 0;
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
