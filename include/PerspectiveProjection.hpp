#ifndef PERSPECTIVE_PROJECTION_HPP
#define PERSPECTIVE_PROJECTION_HPP

#include "Camera.hpp"

class PerspectiveProjection final : public Camera
{
    public:
        PerspectiveProjection(float fov, float nearPlane, float farPlane) 
            : PerspectiveProjection(fov, nearPlane, farPlane, 200, 200) {};
        PerspectiveProjection(float fov, float nearPlane, float faPlane, int _screenHeight, int _screenWidth);
        void render(void) override;
};

#endif