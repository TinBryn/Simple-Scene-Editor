//
// Created by kieran on 22/05/19.
//

#include "math3d/vec.h"

Vec4 Vec4::operator*(Mat4 const &m) const
{
    return Vec4();
}

Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{}

Vec4::Vec4(float s) : Vec4(s, s, s, s)
{}

Vec4 &Vec4::operator+=(Vec4 const &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

Vec4 &Vec4::operator-=(Vec4 const &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

Vec4 &Vec4::operator*=(Vec4 const &v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
}

Vec4 &Vec4::operator/=(Vec4 const &v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
}

Vec4 Vec4::operator+(float s) const
{
    return {x + s, y + s, z + s, w + s};
}

Vec4 Vec4::operator-(float s) const
{
    return {x - s, y - s, y - s, w - s};
}

Vec4 Vec4::operator*(float s) const
{
    return {x * s, y * s, z * s, w * s};
}

Vec4 Vec4::operator/(float s) const
{
    return {x / s, y / s, z / s, w / s};
}

Vec4 Vec4::operator-() const
{
    return {-x, -y, -z, -w};
}

float Vec4::dot(Vec4 const &v) const
{
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

float const *Vec4::data() const
{
    return &x;
}

Vec4 operator+(Vec4 a, Vec4 const &b)
{
    return a += b;
}

Vec4 operator-(Vec4 a, Vec4 const &b)
{
    return a -= b;
}

Vec4 operator*(Vec4 a, Vec4 const &b)
{
    return a *= b;
}

Vec4 operator/(Vec4 a, Vec4 const &b)
{
    return a /= b;
}