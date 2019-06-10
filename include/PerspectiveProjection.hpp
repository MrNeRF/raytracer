#ifndef PERSPECTIVE_PROJECTION_HPP
#define PERSPECTIVE_PROJECTION_HPP

#include "Camera.hpp"
#include "Matrix44.hpp"

class PerspectiveProjection final : public Camera
{
    public:
        PerspectiveProjection(float fov, float nearPlane, float faPlane, int _screenHeight = 200, int _screenWidth = 200);
        virtual ~PerspectiveProjection(void) = default;

        void render(std::vector<std::unique_ptr<Shape>> &objects) override;
        virtual Matrix44f &getProjMat(void)  override {return projectionMatrix;};
    private:
        float nearPlane = 0.1f;
        float farPlane  = 100.f;
};

#endif