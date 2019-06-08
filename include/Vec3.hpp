#ifndef VEC_3_HPP
#define VEC_3_HPP

#include <iostream>
#include <cassert>
#include <cmath>

template <typename T>
class Vec3
{
    public:
        Vec3(T _x, T _y, T _z) : x{_x}, y{_y}, z{_z} {};
        Vec3(const Vec3<T> &v) : x{v.x} , y{v.y}, z{v.z} {};
        bool operator == (const Vec3<T> &v) {return x == v.x && y == v.y && z == v.z;}
        Vec3 operator + (const Vec3 &v) const {return Vec3(x + v.x, y + v.y, z + v.z);}
        Vec3 operator * (const T r) const {return Vec3(x * r, y * r ,z * r);}
        T dot(const Vec3 &v) {return x * v.x + y * v.y + z * v.z;}
        Vec3 cross(const Vec3<T> &v) {return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);}
        T norm() const {return std::sqrt(x * x + y * y + z * z);}
        Vec3& normalize (void) 
        {
            T r  = norm(); 
            assert( r > (T)0);
            r = 1 / r;
            x *= r;
            y *= r;
            z *= r;
            return *this;
        }

        const T& operator [] (uint8_t i) const
        {
            assert(i < 3); 
            return (&x)[i];
        }

        T& operator [] (uint8_t i) 
        {
            assert(i < 3); 
            return (&x)[i];
        }

        friend std::ostream& operator << (std::ostream& s, const Vec3<T> &v)        
        {
            return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ')';
        }

    public:
        T x = 0;
        T y = 0;
        T z = 0;

};

using Vec3f = Vec3<float>;
using Vec3i = Vec3<int>;

#endif