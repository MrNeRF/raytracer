#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <iomanip>
#include <cassert>
#include "Vec3.hpp"

template <typename T>
class Matrix44
{
public:
    T m[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

    Matrix44() {}

    Matrix44(T a, T b, T c, T d, T e, T f, T g, T h,
             T i, T j, T k, T l, T m, T n, T o, T p)
    {
        m[0][0] = a;
        m[0][1] = b;
        m[0][2] = c;
        m[0][3] = d;
        m[1][0] = e;
        m[1][1] = f;
        m[1][2] = g;
        m[1][3] = h;
        m[2][0] = i;
        m[2][1] = j;
        m[2][2] = k;
        m[2][3] = l;
        m[3][0] = m;
        m[3][1] = n;
        m[3][2] = o;
        m[3][3] = p;
    }

    Matrix44(Vec3<T> fstCol, Vec3<T> sndCol, Vec3<T> thdCol)
    {
        m[0][0] = fstCol.x;
        m[0][1] = sndCol.x;
        m[0][2] = thdCol.x;
        m[0][3] = 0;
        m[1][0] = fstCol.y;
        m[1][1] = sndCol.y;
        m[1][2] = thdCol.y;
        m[1][3] = 0;
        m[2][0] = fstCol.z;
        m[2][1] = sndCol.z;
        m[2][2] = thdCol.z;
        m[2][3] = 0;
        m[3][0] = 0;
        m[3][1] = 0;
        m[3][2] = 0;
        m[3][3] = 1;
    }

    const T *operator[](uint8_t i) const
    {
        assert(i < 4);
        return m[i];
    }
    T *operator[](uint8_t i)
    {
        assert(i < 4);
        return m[i];
    }

    const Vec3<T> operator*(const Vec3<T> &v)
    {
        Vec3<T> newVec;
        T tmpVec;
        newVec.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
        newVec.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
        newVec.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
        tmpVec = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3];

        T w = 1 / tmpVec;
        newVec.x *= w;
        newVec.y *= w;
        newVec.x *= w;

        return newVec;
    }

    // Multiply the current matrix with another matrix (rhs)
    Matrix44 operator*(Matrix44 &v) 
    {
        Matrix44 tmp;
        multiply(*this, v, tmp);

        return tmp;
    }

    void multiply(const Matrix44<T> &a, const Matrix44 &b, Matrix44 &c)
    {
        const T *__restrict ap = &a.m[0][0];
        const T *__restrict bp = &b.m[0][0];
        T *__restrict cp = &c.m[0][0];

        T a0, a1, a2, a3;

        a0 = ap[0];
        a1 = ap[1];
        a2 = ap[2];
        a3 = ap[3];

        cp[0] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[1] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[2] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[3] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[4];
        a1 = ap[5];
        a2 = ap[6];
        a3 = ap[7];

        cp[4] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[5] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[6] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[7] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[8];
        a1 = ap[9];
        a2 = ap[10];
        a3 = ap[11];

        cp[8] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[9] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[10] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[11] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[12];
        a1 = ap[13];
        a2 = ap[14];
        a3 = ap[15];

        cp[12] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[13] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[14] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[15] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];
    }

    Matrix44 &transpose()
    {
        Matrix44 tmp(m[0][0],
                     m[1][0],
                     m[2][0],
                     m[3][0],
                     m[0][1],
                     m[1][1],
                     m[2][1],
                     m[3][1],
                     m[0][2],
                     m[1][2],
                     m[2][2],
                     m[3][2],
                     m[0][3],
                     m[1][3],
                     m[2][3],
                     m[3][3]);
        *this = tmp;

        return *this;
    }

    Matrix44 getInverse()
    {
        int i, j, k;
        Matrix44 s;
        Matrix44 t(*this);

        // Forward elimination
        for (i = 0; i < 3; i++)
        {
            int pivot = i;

            T pivotsize = t[i][i];

            if (pivotsize < 0)
                pivotsize = -pivotsize;

            for (j = i + 1; j < 4; j++)
            {
                T tmp = t[j][i];

                if (tmp < 0)
                    tmp = -tmp;

                if (tmp > pivotsize)
                {
                    pivot = j;
                    pivotsize = tmp;
                }
            }

            if (pivotsize == 0)
            {
                // Cannot invert singular matrix
                return Matrix44();
            }

            if (pivot != i)
            {
                for (j = 0; j < 4; j++)
                {
                    T tmp;

                    tmp = t[i][j];
                    t[i][j] = t[pivot][j];
                    t[pivot][j] = tmp;

                    tmp = s[i][j];
                    s[i][j] = s[pivot][j];
                    s[pivot][j] = tmp;
                }
            }

            for (j = i + 1; j < 4; j++)
            {
                T f = t[j][i] / t[i][i];

                for (k = 0; k < 4; k++)
                {
                    t[j][k] -= f * t[i][k];
                    s[j][k] -= f * s[i][k];
                }
            }
        }

        // Backward substitution
        for (i = 3; i >= 0; --i)
        {
            T f;

            if ((f = t[i][i]) == 0)
            {
                // Cannot invert singular matrix
                return Matrix44();
            }

            for (j = 0; j < 4; j++)
            {
                t[i][j] /= f;
                s[i][j] /= f;
            }

            for (j = 0; j < i; j++)
            {
                f = t[j][i];

                for (k = 0; k < 4; k++)
                {
                    t[j][k] -= f * t[i][k];
                    s[j][k] -= f * s[i][k];
                }
            }
        }

        return s;
    }

    // \brief set current matrix to its inverse
    const Matrix44<T> &invert()
    {
        *this = getInverse();
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &s, const Matrix44 &mat)
    {
        std::ios_base::fmtflags oldFlags = s.flags();
        int width = 12; // total with of the displayed number
        s.precision(5); // control the number of displayed decimals
        s.setf(std::ios_base::fixed);

        s << "(" << std::setw(width) << mat[0][0] << " " << std::setw(width) << mat[0][1] << " " << std::setw(width) << mat[0][2] << " " << std::setw(width) << mat[0][3] << "\n";
        s << " " << std::setw(width) << mat[1][0] << " " << std::setw(width) << mat[1][1] << " " << std::setw(width) << mat[1][2] << " " << std::setw(width) << mat[1][3] << "\n";
        s << " " << std::setw(width) << mat[2][0] << " " << std::setw(width) << mat[2][1] << " " << std::setw(width) << mat[2][2] << " " << std::setw(width) << mat[2][3] << "\n";
        s << " " << std::setw(width) << mat[3][0] << " " << std::setw(width) << mat[3][1] << " " << std::setw(width) << mat[3][2] << " " << std::setw(width) << mat[3][3] << ")\n";

        s.flags(oldFlags);
        return s;
    }
};

using Matrix44f = Matrix44<float>;
#endif