//
// Created by kieran on 22/05/19.
//

#include <iostream>
#include <cmath>
#include <math3d/vec.h>
#include "math3d/mat.h"

Mat4 operator+(Mat4 a, Mat4 const &b)
{
    return a += b;
}

Mat4 operator-(Mat4 a, Mat4 const &b)
{
    return a -= b;
}

Mat4 operator*(Mat4 const &a, Mat4 const &b)
{
    return {a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12],
            a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13],
            a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14],
            a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15],
            a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12],
            a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13],
            a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14],
            a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15],
            a[8] * b[0] + a[9] * b[4] + a[10] * b[8] + a[11] * b[12],
            a[8] * b[1] + a[9] * b[5] + a[10] * b[9] + a[11] * b[13],
            a[8] * b[2] + a[9] * b[6] + a[10] * b[10] + a[11] * b[14],
            a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11] * b[15],
            a[12] * b[0] + a[13] * b[4] + a[14] * b[8] + a[15] * b[12],
            a[12] * b[1] + a[13] * b[5] + a[14] * b[9] + a[15] * b[13],
            a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14],
            a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]};
}

Mat4::Mat4(float e11, float e12, float e13, float e14,
           float e21, float e22, float e23, float e24,
           float e31, float e32, float e33, float e34,
           float e41, float e42, float e43, float e44) :
        e11(e11), e12(e12), e13(e13), e14(e14),
        e21(e21), e22(e22), e23(e23), e24(e24),
        e31(e31), e32(e32), e33(e33), e34(e34),
        e41(e41), e42(e42), e43(e43), e44(e44)
{}

Mat4::Mat4(float s) : Mat4(s, 0, 0, 0,
                           0, s, 0, 0,
                           0, 0, s, 0,
                           0, 0, 0, s)
{}

Mat4 &Mat4::operator+=(Mat4 const &m)
{
    for (int i = 0; i < 16; i++)
    {
        data[i] += m.data[i];
    }
    return *this;
}

Mat4 &Mat4::operator-=(Mat4 const &m)
{
    for (int i = 0; i < 16; i++)
    {
        data[i] -= m.data[i];
    }
    return *this;
}

Mat4 &Mat4::operator*=(Mat4 const &m)
{
    return *this = *this * m;
}

float &Mat4::operator[](int i)
{ return data[i]; }

float const &Mat4::operator[](int i) const
{ return data[i]; }

Mat4 Mat4::rotatedXY(float angle)
{
    float s = std::sin(angle);
    float c = std::cos(angle);

    return {e11 * c - e21 * s, e12 * c - e22 * s, e13 * c - e23 * s, 0,
            e11 * s + e21 * c, e12 * s + e22 * c, e13 * s + e23 * c, 0,
            e31, e32, e33, 0,
            0, 0, 0, 1};
}

Mat4 Mat4::rotatedYZ(float angle)
{
    float s = std::sin(angle);
    float c = std::cos(angle);
    return {e11, e12, e13, 0,
            e21 * c - e31 * s, e22 * c - e32 * s, e23 * c - e33 * s, 0,
            e21 * s + e31 * c, e22 * s + e32 * c, e23 * s + e33 * c, 0,
            0, 0, 0, 1};
}

Mat4 Mat4::rotatedZX(float angle)
{
    float s = std::sin(angle);
    float c = std::cos(angle);
    return {e31 * s + e11 * c, e32 * s + e12 * c, e33 * s + e13 * c, 0,
            e21, e22, e23, 0,
            e31 * c - e11 * s, e32 * c - e12 * s, e33 * c - e13 * s, 0,
            0, 0, 0, 1};
}

Mat4 Mat4::scaled(float xs, float ys, float zs)
{
    return {e11 * xs, e12 * xs, e13 * xs, e14 * xs,
            e21 * ys, e22 * ys, e23 * ys, e24 * ys,
            e31 * zs, e32 * zs, e33 * zs, e34 * zs,
            0, 0, 0, 1};
}

Mat4 Mat4::translated(float xt, float yt, float zt)
{
    return {e11, e12, e13, e14 + xt,
            e21, e22, e23, e24 + yt,
            e31, e32, e33, e34 + zt,
            0, 0, 0, 1};
}

Mat4 Mat4::translated(Vec3 const &v)
{
    return translated(v.x, v.y, v.z);
}

Mat4 Mat4::perspective(float xfov, float yfov, float near, float far)
{
    float xs = xfov;
    float ys = yfov;

    float diff = near - far;
    float zs = (near + far) / diff;
    float p = 2 * near * far;
    return {e11 * xs, e12 * xs, e13 * xs, e14 * xs,
            e21 * ys, e22 * ys, e23 * ys, e24 * ys,
            e31 * zs, e32 * zs, e33 * zs, e34 * zs + p,
            -e31, -e32, -e33, -e34};
}

Mat4 Mat4::ortho(float top, float bottom, float left, float right, float near, float far)
{
    float xs = 2 / (right - left);
    float ys = 2 / (top - bottom);
    float zs = 2 / (far - near);
    float xt = -(left + right) / 2;
    float yt = -(top + bottom) / 2;
    float zt = -(far + near) / 2;
    return {e11 * xs, e12 * xs, e13 * xs, (e14 + xt) * xs,
            e21 * ys, e22 * ys, e23 * ys, (e24 + yt) * ys,
            e31 * zs, e32 * zs, e33 * zs, (e34 + zt) * zs,
            0, 0, 0, 1};
}

Mat3 Mat4::mat3()
{
    return {e11, e12, e13,
            e21, e22, e23,
            e31, e32, e33};
}

Mat2 Mat4::mat2()
{
    return {e11, e12,
            e21, e22};
}

Mat4::Mat4(Mat3 const &m) : Mat4{m.e11, m.e12, m.e13, 0,
                                 m.e21, m.e22, m.e23, 0,
                                 m.e31, m.e32, m.e33, 0,
                                 0, 0, 0, 1}
{}

Mat4::Mat4(Mat2 const &m) : Mat4{m.e11, m.e12, 0, 0,
                                 m.e21, m.e22, 0, 0,
                                 0, 0, 1, 0,
                                 0, 0, 0, 1}
{}

Mat4 Mat4::scaled(float s)
{
    return scaled(s, s, s);
}

Mat4 lookat(Vec3 const &from, Vec3 const &to, Vec3 const &up, float fov, float aspect, float near, float far)
{
    return Mat4(1)
            .translated(-from);
}

Vec4 operator*(Mat4 const &m, Vec4 const &b)
{
    return {m[0] * b.x + m[1] * b.y + m[2] * b.z + m[3] * b.w,
            m[4] * b.x + m[5] * b.y + m[6] * b.z + m[7] * b.w,
            m[8] * b.x + m[9] * b.y + m[10] * b.z + m[11] * b.w,
            m[12] * b.x + m[13] * b.y + m[14] * b.z + m[15] * b.w};
}

std::ostream &operator <<(std::ostream& os, Mat4 const&mat)
{
    os << mat[0] << ", " << mat[1]<< ", " << mat[2]<< ", " << mat[3] << std::endl;
    os << mat[4] << ", " << mat[5]<< ", " << mat[6]<< ", " << mat[7] << std::endl;
    os << mat[8] << ", " << mat[9]<< ", " << mat[10]<< ", " << mat[11] << std::endl;
    os << mat[12] << ", " << mat[13]<< ", " << mat[14]<< ", " << mat[15] << std::endl;
}

Mat4 perspective(float width, float height, float near, float far)
{
    float a = 1.0 / width;
    float b = 1.0 / height;
    float c = (near + far) / (far - near);
    float d = 2 * near * far / (near - far);

    return {a, 0, 0, 0,
            0, b, 0, 0,
            0, 0, c, d,
            0, 0, 1, 0};
}
