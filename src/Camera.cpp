#include "Camera.hpp"
#include "cmath"



Camera::Camera(float _fov, int _screenWidth, int _screenHeight) : 
    fov{_fov},
    screenWidth{_screenWidth}, 
    screenHeight{_screenHeight}
{
    imageAspectRatio = screenWidth / static_cast<float>(screenHeight);
    scale = std::tan(deg2rad(fov * 0.5));
}

void Camera::setLookAtMatrix(const Vec3f& v_fwd, const Vec3f& v_right, const Vec3f& v_up)
{
    forward  = v_fwd; 
    right    = v_right;
    up       = v_up;

    view = Matrix44f(forward, right, up);
}


float Camera::deg2rad(float degrees)
{
    return degrees * 4.0 * std::atan(1.0) / 180.0f;
}
