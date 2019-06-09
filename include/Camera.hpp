#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix44.hpp"
#include "Vec3.hpp"

class Camera
{
    public:
        Camera(float _fov) : Camera(_fov, 200, 200) {};
        Camera(float fov, int _screenWidth, int _screenHeight);
        virtual ~Camera(void) = default;
        virtual void render() = 0;
    
    protected:
        float deg2rad(float degrees);
        void setLookAtMatrix(const Vec3f& v_fwd, const Vec3f& v_right, const Vec3f& v_up);

    protected:
        int screenWidth, screenHeight;
        float imageAspectRatio = 1.0;
        float scale;
        float fov;
        Vec3f forward   = Vec3f(0.f, 0.f, 1.f);
        Vec3f up        = Vec3f(0.f, 1.f, 0.f);
        Vec3f right     = Vec3f(1.f, 0.f, 0.f);
        Matrix44f view = Matrix44f(forward, up, right);
};

#endif