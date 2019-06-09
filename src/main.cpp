#include <iostream>
#include "Vec3.hpp"
#include "Matrix44.hpp"
#include <cassert>

int main()
{
    Vec3f v1(1.0, 0.0, 0.0);
    Vec3f v2(2.2, 1.0, 1.2);
    Vec3f v3(0.0, 1.0, 0.0);

    std::cout << v1 + v2 << std::endl;
    std::cout << v2 * 3.f  << std::endl;
    std::cout << v2.norm() << std::endl;
    std::cout << v1.cross(v3) << std::endl;
    std::cout << v2.normalize() << std::endl;

    Matrix44f m;
    std::cout << m << std::endl;

    return 0;
}