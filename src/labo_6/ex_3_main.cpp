// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

import std;
import vector3d;

int main()
try
{
    Vector3D vec_1{X{1.1}, Y{2.2}, Z{3.3}};
    Vector3D vec_2{X{3.3}, Y{1.1}, Z{2.2}};
    Vector3D vec_3{vec_1 + vec_2};
    Vector3D vec_4{vec_1 - vec_2};
    Vector3D vec_5{vec_4 * std::numbers::pi};

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
}
catch (std::exception const& e)
{
    std::cerr << e.what() << '\n';
    return 1;
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
