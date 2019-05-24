//
// Created by kieran on 22/05/19.
//

#include "math3d/vec.h"

Vec2 operator/(Vec2 a, Vec2 const &b)
{
    return a /= b;
}

Vec2 operator*(Vec2 a, Vec2 const &b)
{
    return a *= b;
}

Vec2 operator-(Vec2 a, Vec2 const &b)
{
    return a -= b;
}

Vec2 operator+(Vec2 a, Vec2 const &b)
{
    return a += b;
}

Vec2::Vec2(Vec3 const &v) : x(v.x), y(v.y)
{}

Vec2::Vec2(Vec4 const &v) : x(v.x), y(v.y)
{}

Vec2::Vec2(float s) : Vec2(s, s)
{}

Vec2::Vec2(float x, float y) : x(x), y(y)
{}

Vec2 &Vec2::operator+=(Vec2 const &v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vec2 &Vec2::operator-=(Vec2 const &v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vec2 &Vec2::operator*=(Vec2 const &v)
{
    x *= v.x;
    y *= v.y;
    return *this;
}

Vec2 &Vec2::operator/=(Vec2 const &v)
{
    x /= v.x;
    y /= v.y;
    return *this;
}

Vec2 Vec2::operator+(float s) const
{
    return {x + s, y + s};
}

Vec2 Vec2::operator-(float s) const
{
    return {x - s, y - s};
}

Vec2 Vec2::operator*(float s) const
{
    return {x * s, y * s};
}

Vec2 Vec2::operator/(float s) const
{
    return {x / s, y / s};
}

Vec2 Vec2::operator-() const
{
    return {-x, -y};
}

float Vec2::dot(Vec2 const &v) const
{
    return x * v.x + y * v.y;
}

float const *Vec2::data() const
{
    return &x;
}
