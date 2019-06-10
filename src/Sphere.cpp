#include "Sphere.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

bool Sphere::intersect(const Vec3f &orig, const Vec3f &dir, float &t) 
{
    float t0, t1;
    Vec3f L = orig - center;
    float a = dir.dot(dir);
    float b = 2 * dir.dot(L);
    float c = L.dot(L) - radius2;
    if(!solveQuadratic(a, b, c, t0, t1)) 
    {
        return false;
    }

    if (t0 > t1)
    {
        std::swap(t0, t1);
    }

    if (t0 < 0)
    {
        t0 = t1;
        if (t0 < 0)
        {
            return false;
        }
    }

    t = t0;
    return true;
}

void Sphere::getSurfaceData(const Vec3f &pHit, Vec3f& nHit, Vec2f &tex) const
{
    nHit = pHit - center;
    nHit.normalize();

    tex.x = (1 + std::atan2(nHit.z, nHit.x) / M_PI) * 0.5f;
    tex.y = std::acos(nHit.y) / M_PI;

}