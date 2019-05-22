//
// Created by kieran on 22/05/19.
//

#include "vec.h"

Vec3 operator/(Vec3 a, Vec3 const &b)
{
    return a /= b;
}

Vec3 operator*(Vec3 a, Vec3 const &b)
{
    return a *= b;
}

Vec3 operator-(Vec3 a, Vec3 const &b)
{
    return a -= b;
}

Vec3 operator+(Vec3 a, Vec3 const &b)
{
    return a += b;
}

Vec3::Vec3(Vec4 const &v) : x(v.x), y(v.y), z(v.z)
{}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z)
{}

Vec3::Vec3(float s) : Vec3(s, s, s)
{}

Vec3 &Vec3::operator+=(Vec3 const &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3 &Vec3::operator-=(Vec3 const &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec3 &Vec3::operator*=(Vec3 const &v)
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

Vec3 &Vec3::operator/=(Vec3 const &v)
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

Vec3 Vec3::operator+(float s) const
{
    return {x + s, y + s, z + s};
}

Vec3 Vec3::operator-(float s) const
{
    return {x - s, y - s, y - s};
}

Vec3 Vec3::operator*(float s) const
{
    return {x * s, y * s, z * s};
}

Vec3 Vec3::operator/(float s) const
{
    return {x / s, y / s, z / s};
}

Vec3 Vec3::operator-() const
{
    return {-x, -y, -z};
}

float Vec3::dot(Vec3 const &v) const
{
    return x * v.x + y * v.y + z * v.z;
}
