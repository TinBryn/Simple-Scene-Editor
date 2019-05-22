//
// Created by kieran on 22/05/19.
//

#include <cmath>
#include "mat.h"


Mat2::Mat2(float e11, float e12,
           float e21, float e22) :
        e11(e11), e12(e12),
        e21(e21), e22(e22)
{}

Mat2::Mat2(float s) : Mat2(s, 0,
                           0, s)
{}

float &Mat2::operator[](int i)
{
    return data[i];
}

float const &Mat2::operator[](int i) const
{
    return data[i];
}

Mat2 &Mat2::operator+=(Mat2 const &m)
{
    for (int i = 0; i < 4; i++)
    {
        data[i] += m.data[i];
    }
    return *this;
}

Mat2 &Mat2::operator-=(Mat2 const &m)
{
    for (int i = 0; i < 4; i++)
    {
        data[i] -= m.data[i];
    }
    return *this;
}

Mat2 &Mat2::operator*=(Mat2 const &m)
{
    return *this = *this * m;
}

Mat2 operator+(Mat2 a, Mat2 const &b)
{
    return a += b;
}

Mat2 operator-(Mat2 a, Mat2 const &b)
{
    return a -= b;
}

Mat2 operator*(Mat2 const &a, Mat2 const &b)
{
    return {a[0] * b[0] + a[1] * b[2],
            a[0] * b[1] + a[1] * b[3],
            a[2] * b[0] + a[3] * b[2],
            a[2] * b[1] + a[3] * b[3]};
}

Mat2 Mat2::rotated(float angle)
{
    float s = std::sin(angle);
    float c = std::cos(angle);
    return {e11 * c - e21 * s, e12 * c - e22 * s,
            e11 * s + e21 * c, e12 * s + e22 * c};
}

Mat2 Mat2::scaled(float xs, float ys)
{
    return {e11 * xs, e12 * xs,
            e21 * ys, e22 * ys};
}