#include "PerspectiveProjection.hpp"
#include <fstream>

namespace
{
    float clamp(const float &lo, const float &hi, const float &v)
    {
        return std::max(lo, std::min(hi, v));
    }
}

PerspectiveProjection::PerspectiveProjection(float _fov, float _nearPlane, float _farPlane,
                                                int _screenHeight, int _screenWidth) :
    Camera(_fov, _screenHeight, _screenWidth) 
{
    nearPlane = _nearPlane; 
    farPlane = _farPlane;

    float farNearDiff = 1.0f / (farPlane - nearPlane);
    projectionMatrix[0][0] = scale;    
    projectionMatrix[1][1] = scale;    
    projectionMatrix[2][2] = -farPlane * farNearDiff;    
    projectionMatrix[3][3] =  0.0f;   
    projectionMatrix[2][3] = -farPlane * nearPlane * farNearDiff;    
    projectionMatrix[3][2] = -1.;    

    worldToScreen = projectionMatrix * view;
}

void PerspectiveProjection::render(std::vector<std::unique_ptr<Shape>> &objects)
{
   std::vector<Vec3f> frameBuffer(screenHeight * screenWidth);
   Vec3f orig = view * orig;

    for(int i = 0; i < screenHeight; ++i)
    {
        for(int j = 0; j < screenWidth; ++j)
        {
            float x = (2 * (j + 0.5) / static_cast<float>(screenWidth) - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (i + 0.5) / static_cast<float>(screenHeight)) * scale;

            Vec3f dir = view * Vec3f(x, y, -1.0f);
            dir.normalize();
            frameBuffer[i * screenHeight + j] = castRay(orig, dir, objects);
        }
    }

     // Save result to a PPM image (keep these flags if you compile under Windows)
    std::ofstream ofs("./out.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << screenHeight<< " " << screenWidth << "\n255\n";
    for (int i = 0; i < screenHeight * screenWidth; ++i) 
    {
        char r = (char)(255 * clamp(0.f, 1.f, frameBuffer[i].x));
        char g = (char)(255 * clamp(0.f, 1.f, frameBuffer[i].y));
        char b = (char)(255 * clamp(0.f, 1.f, frameBuffer[i].z));
        ofs << r << g << b;
    }

    ofs.close(); 
}