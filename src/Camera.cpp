#include "Camera.hpp"
#include "Vec2.hpp"
#include <cmath>
#include <limits>

namespace
{
    Vec3f mix(const Vec3f &a, const Vec3f& b, const float &mixValue)
    {
        return a * (1 - mixValue) + b * mixValue;
    }
}

Camera::Camera(float _fov, int _screenWidth, int _screenHeight) : fov{_fov},
                                                                  screenWidth{_screenWidth},
                                                                  screenHeight{_screenHeight}
{
    imageAspectRatio = screenWidth / static_cast<float>(screenHeight);
    scale = std::tan(deg2rad(fov * 0.5));
}

bool Camera::traceRay(const Vec3f &orig,
                      const Vec3f &dir,
                      const std::vector<std::unique_ptr<Shape>> &objects,
                      float tNear,
                      const Shape *&hitObject)
{
    tNear = std::numeric_limits<float>::max();
    std::vector<std::unique_ptr<Shape>>::const_iterator iter = objects.begin();
    for (; iter != objects.end(); ++iter)
    {
        float t = std::numeric_limits<float>::max();
        if ((*iter)->intersect(orig, dir, t) && t < tNear)
        {
            hitObject = iter->get();
        }
    }

    return (hitObject != nullptr);
}

Vec3f Camera::castRay(const Vec3f &orig,
                      const Vec3f &dir,
                      const std::vector<std::unique_ptr<Shape>> &objects)
{
    Vec3f hitColor;
    const Shape *hitObject = nullptr;
    float t = 0;
    if(traceRay(orig, dir, objects, t, hitObject))
    {
        Vec3f pHit = orig + dir * t;
        Vec3f nHit;
        Vec2f tex;
        hitObject->getSurfaceData(pHit, nHit, tex);
        float scale = 4.f;
        float pattern = (fmodf(tex.x * scale, 1) > 0.5) ^ (fmodf(tex.y * scale, 1) > 0.5);
        hitColor = mix(hitObject->color, hitObject->color * 0.8, pattern) * std::max(0.f, nHit.dot(dir * -1));
    }
    return hitColor;
}

void Camera::setLookAtMatrix(const Vec3f &v_fwd, const Vec3f &v_right, const Vec3f &v_up)
{
    forward = v_fwd;
    right = v_right;
    up = v_up;

    view = Matrix44f(forward, right, up);
}

float Camera::deg2rad(float degrees)
{
    return degrees * 4.0 * std::atan(1.0) / 180.0f;
}
