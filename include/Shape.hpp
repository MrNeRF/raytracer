#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Vec3.hpp"
#include "Vec2.hpp"

class Shape
{
    public:
        Shape(void) = default; 
        virtual ~Shape(void) = default; 

        virtual bool intersect(const Vec3f &, const Vec3f &, float &) = 0;
        virtual void getSurfaceData(const Vec3f &, Vec3f &, Vec2f &) const = 0;
        bool solveQuadratic(const float a, const float b, const float c, float &x0, float &x1);
        Vec3f color = Vec3f(0.1f, 0.2f, 0.3f);
};

#endif