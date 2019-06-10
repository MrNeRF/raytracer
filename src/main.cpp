#include <iostream>
#include "Vec3.hpp"
#include "Matrix44.hpp"
#include "PerspectiveProjection.hpp"
#include "Sphere.hpp"
#include "Shape.hpp"
#include <cassert>

int main()
{
    std::vector<std::unique_ptr<Shape>> objects;
    objects.push_back(std::make_unique<Sphere>(Vec3f(1,1,1), 50));

    PerspectiveProjection cam(51, 0.1, 100, 640, 480);
    cam.render(objects);
    return 0;
}