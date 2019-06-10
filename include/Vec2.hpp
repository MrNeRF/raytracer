
#ifndef VEC_2_HPP
#define VEC_2_HPP

#include <iostream>
#include <cassert>
#include <cmath>

template <typename T>
class Vec2
{
    public:
        Vec2(void) = default;
        Vec2(T _x, T _y) : x{_x}, y{_y} {};
        Vec2(const Vec2<T> &v) : x{v.x} , y{v.y} {};
        bool operator == (const Vec2<T> &v) {return x == v.x && y == v.y;}
        Vec2 operator + (const Vec2 &v) const {return Vec2(x + v.x, y + v.y);}
        Vec2 operator * (const T r) const {return Vec2(x * r, y * r );}
        T dot(const Vec2 &v) {return x * v.x + y * v.y;}
        T norm() const {return std::sqrt(x * x + y * y);}
        Vec2& normalize (void) 
        {
            T r  = norm(); 
            assert( r > (T)0);
            r = 1 / r;
            x *= r;
            y *= r;
            return *this;
        }

        const T& operator [] (uint8_t i) const
        {
            assert(i < 2); 
            return (&x)[i];
        }

        T& operator [] (uint8_t i) 
        {
            assert(i < 2); 
            return (&x)[i];
        }

        friend std::ostream& operator << (std::ostream& s, const Vec2<T> &v)        
        {
            return s << '(' << v.x << ' ' << v.y  << ')';
        }

    public:
        T x = 0;
        T y = 0;

};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;

#endif