//
// Created by kieran on 22/05/19.
//

#ifndef CITS3003_VEC_H
#define CITS3003_VEC_H

#include "fwdtypes.h"
#include <iosfwd>

struct Vec2
{
    Vec2() = default;

    Vec2(Vec2 const &v) = default;

    Vec2(float x, float y);

    explicit Vec2(float s);

    explicit Vec2(Vec3 const &v);

    explicit Vec2(Vec4 const &v);

    Vec2 &operator=(Vec2 const &v) = default;

    Vec2 &operator+=(Vec2 const &v);

    Vec2 &operator-=(Vec2 const &v);

    Vec2 &operator*=(Vec2 const &v);

    Vec2 &operator/=(Vec2 const &v);

    Vec2 operator+(float s) const;

    Vec2 operator-(float s) const;

    Vec2 operator*(float s) const;

    Vec2 operator/(float s) const;

    Vec2 operator-() const;

    float dot(Vec2 const &v) const;

    float const *data() const;

    float x;
    float y;
};

struct Vec3
{
    Vec3() = default;

    Vec3(Vec3 const &v) = default;

    Vec3(float x, float y, float z);

    explicit Vec3(float s);

    explicit Vec3(Vec4 const &v);

    Vec3 &operator=(Vec3 const &v) = default;

    Vec3 &operator+=(Vec3 const &v);

    Vec3 &operator-=(Vec3 const &v);

    Vec3 &operator*=(Vec3 const &v);

    Vec3 &operator/=(Vec3 const &v);

    Vec3 operator+(float s) const;

    Vec3 operator-(float s) const;

    Vec3 operator*(float s) const;

    Vec3 operator/(float s) const;

    Vec3 operator-() const;

    float dot(Vec3 const &v) const;

    Vec3 cross(Vec3 const &v) const;

    float const *data() const;

    float x;
    float y;
    float z;
};

struct Vec4
{
    Vec4() = default;

    Vec4(Vec4 const &v) = default;

    Vec4(float x, float y, float z, float w);

    explicit Vec4(float s);

    Vec4 &operator=(Vec4 const &v) = default;

    Vec4 &operator+=(Vec4 const &v);

    Vec4 &operator-=(Vec4 const &v);

    Vec4 &operator*=(Vec4 const &v);

    Vec4 &operator/=(Vec4 const &v);

    Vec4 operator+(float s) const;

    Vec4 operator-(float s) const;

    Vec4 operator*(float s) const;

    Vec4 operator/(float s) const;

    Vec4 operator-() const;

    Vec4 operator*(Mat4 const &m) const;

    float dot(Vec4 const &v) const;

    float const *data() const;

    float x;
    float y;
    float z;
    float w;
};

//Vec2 operations

Vec2 operator+(Vec2 a, Vec2 const &b);

Vec2 operator-(Vec2 a, Vec2 const &b);

Vec2 operator*(Vec2 a, Vec2 const &b);

Vec2 operator/(Vec2 a, Vec2 const &b);

std::ostream &operator<<(std::ostream &os, Vec3 &v);

//Vec3 operations

Vec3 operator+(Vec3 a, Vec3 const &b);

Vec3 operator-(Vec3 a, Vec3 const &b);

Vec3 operator*(Vec3 a, Vec3 const &b);

Vec3 operator/(Vec3 a, Vec3 const &b);

//Vec4 operations

Vec4 operator+(Vec4 a, Vec4 const &b);

Vec4 operator-(Vec4 a, Vec4 const &b);

Vec4 operator*(Vec4 a, Vec4 const &b);

Vec4 operator/(Vec4 a, Vec4 const &b);

#endif //CITS3003_VEC_H
