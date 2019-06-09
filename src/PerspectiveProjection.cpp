#include "PerspectiveProjection.hpp"

PerspectiveProjection::PerspectiveProjection(float fov, float nearPlane, float farPlane,
                                                int _screenHeight, int _screenWidth) :
    Camera(fov, _screenHeight, _screenWidth)
{

}