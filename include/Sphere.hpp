#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Shape.hpp"
#include "Vec3.hpp"

class Sphere : public Shape
{
    public:
        Sphere(const Vec3f &c, const float &r) : radius(r), radius2(r * r), center(c) {}
        bool intersect(const Vec3f &orig, const Vec3f &dir, float &t) override;
        void getSurfaceData(const Vec3f &pHit, Vec3f& nHit, Vec2f &tex) const override;
    public:
        float radius;
        float radius2;
        Vec3f center;
};

#endif