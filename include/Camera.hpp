#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix44.hpp"
#include "Vec3.hpp"
#include "Shape.hpp"
#include <memory>
#include <vector>

class Camera
{
    public:
        Camera(float _fov) : Camera(_fov, 200, 200) {};
        Camera(float fov, int _screenWidth, int _screenHeight);
        virtual ~Camera(void) = default;
        virtual void render(std::vector<std::unique_ptr<Shape>> &objects) = 0;
        virtual Matrix44f &getProjMat(void) = 0;
        Matrix44f &getCamMat(void) {return view;};
    
    protected:
        float deg2rad(float degrees);
        void setLookAtMatrix(const Vec3f& v_fwd, const Vec3f& v_right, const Vec3f& v_up);
        bool traceRay(const Vec3f &orig, const Vec3f &dir, const std::vector<std::unique_ptr<Shape>> &objects, float tNear, const Shape *&hitObject);
        Vec3f castRay(const Vec3f &orig, const Vec3f &dir, const std::vector<std::unique_ptr<Shape>> &objects);

    protected:
        float fov;
        float imageAspectRatio = 1.0;
        int screenWidth;
        int screenHeight;
        float scale;
        Vec3f forward           = Vec3f(0.f, 0.f, 1.f);
        Vec3f up                = Vec3f(0.f, 1.f, 0.f);
        Vec3f right             = Vec3f(1.f, 0.f, 0.f);
        Matrix44f view          = Matrix44f(forward, up, right);
        Matrix44f worldToScreen; 
        Matrix44f projectionMatrix;
};

#endif