//
// Created by kieran on 22/05/19.
//

#include <cmath>
#include "mat.h"

Mat3::Mat3(float e11, float e12, float e13,
           float e21, float e22, float e23,
           float e31, float e32, float e33) :
        e11(e11), e12(e12), e13(e13),
        e21(e21), e22(e22), e23(e23),
        e31(e31), e32(e32), e33(e33)
{}

Mat3::Mat3(float s) : Mat3(s, 0, 0,
                           0, s, 0,
                           0, 0, s)
{}

Mat3 &Mat3::operator+=(Mat3 const &m)
{
    for (int i = 0; i < 9; i++)
    {
        data[i] += m.data[i];
    }
    return *this;
}

Mat3 &Mat3::operator-=(Mat3 const &m)
{
    for (int i = 0; i < 9; i++)
    {
        data[i] -= m.data[i];
    }
    return *this;
}

Mat3 &Mat3::operator*=(Mat3 const &m)
{
    return *this = *this * m;
}

float &Mat3::operator[](int i)
{ return data[i]; }

float const &Mat3::operator[](int i) const
{ return data[i]; }

Mat3 Mat3::rotatedXY(float angle)
{
    float s = std::sin(angle);
    float c = std::cos(angle);

    return {e11 * c - e21 * s, e12 * c - e22 * s, e13 * c - e23 * s,
            e11 * s + e21 * c, e12 * s + e22 * c, e13 * s + e23 * c,
            e31, e32, e33};
}

Mat3 Mat3::rotatedYZ(float angle)
{
    float s = std::sin(angle);
    float c = std::cos(angle);
    return {e11, e12, e13,
            e21 * c - e31 * s, e22 * c - e32 * s, e23 * c - e33 * s,
            e21 * s + e31 * c, e22 * s + e32 * c, e23 * s + e33 * c};
}

Mat3 Mat3::rotatedZX(float angle)
{
    float s = std::sin(angle);
    float c = std::cos(angle);
    return {e31 * s + e11 * c, e32 * s + e12 * c, e33 * s + e13 * c,
            e21, e22, e23,
            e31 * c - e11 * s, e32 * c - e12 * s, e33 * c - e13 * s};
}

Mat3 Mat3::scaled(float xs, float ys, float zs)
{
    return Mat3{
            e11 * xs, e12 * xs, e13 * xs,
            e21 * ys, e22 * ys, e23 * ys,
            e31 * zs, e32 * zs, e33 * zs};
}

Mat2 Mat3::mat2()
{
    return {e11, e12,
            e21, e22};
}

Mat3::Mat3(Mat2 const &m) : Mat3{m.e11, m.e12, 0,
                                 m.e21, m.e22, 0,
                                 0, 0, 1}
{}

Mat3 operator+(Mat3 a, Mat3 const &b)
{
    return a += b;
}

Mat3 operator-(Mat3 a, Mat3 const &b)
{
    return a -= b;
}

Mat3 operator*(Mat3 const &a, Mat3 const &b)
{
    /*
     * a0 b0 + a1 b3 + a2 b6    a0 b1 + a1 b4 + a2 b7   a0 b2 + a1 b5 + a2 b8
     * a3 b0 + a4 b3 + a5 b6    a3 b1 + a4 b4 + a5 b7   a3 b2 + a4 b5 + a5 b8
     * a6 b0 + a7 b3 + a8 b6    a6 b1 + a7 b4 + a8 b7   a6 b2 + a7 b5 + a8 b8
     */

    return {a[0] * b[0] + a[1] * b[3] + a[2] * b[6],
            a[0] * b[1] + a[1] * b[4] + a[2] * b[7],
            a[0] * b[2] + a[1] * b[5] + a[2] * b[8],
            a[3] * b[0] + a[4] * b[3] + a[5] * b[6],
            a[3] * b[1] + a[4] * b[4] + a[5] * b[7],
            a[3] * b[2] + a[4] * b[5] + a[5] * b[8],
            a[6] * b[0] + a[7] * b[3] + a[8] * b[6],
            a[6] * b[1] + a[7] * b[4] + a[8] * b[7],
            a[6] * b[2] + a[7] * b[5] + a[8] * b[8]};
}