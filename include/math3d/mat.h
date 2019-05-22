//
// Created by kieran on 22/05/19.
//

#ifndef CITS3003_MAT_H
#define CITS3003_MAT_H

#include "fwdtypes.h"

struct Mat2
{
    Mat2() = default;

    Mat2(Mat2 const &) = default;

    Mat2(float e11, float e12,
         float e21, float e22);

    explicit Mat2(float s);

    Mat2 &operator=(Mat2 const &) = default;

    float &operator[](int i);

    float const &operator[](int i) const;

    Mat2 &operator+=(Mat2 const &m);

    Mat2 &operator-=(Mat2 const &m);

    Mat2 &operator*=(Mat2 const &m);

    Mat2 rotated(float angle);

    Mat2 scaled(float xs, float ys);

    union
    {
        float data[4];
        struct
        {
            float e11;
            float e12;
            float e21;
            float e22;
        };
    };
};

Mat2 operator+(Mat2 a, Mat2 const &b);

Mat2 operator-(Mat2 a, Mat2 const &b);

Mat2 operator*(Mat2 const &a, Mat2 const &b);

struct Mat3
{
    Mat3() = default;

    Mat3(Mat3 const &) = default;

    explicit Mat3(Mat2 const&);

    Mat3(float e11, float e12, float e13,
         float e21, float e22, float e23,
         float e31, float e32, float e33);

    explicit Mat3(float s);

    Mat3 &operator=(Mat3 const &) = default;

    Mat3 &operator+=(Mat3 const &m);

    Mat3 &operator-=(Mat3 const &m);

    Mat3 &operator*=(Mat3 const &m);

    float &operator[](int i);

    float const &operator[](int i) const;

    Mat3 rotatedXY(float angle);

    Mat3 rotatedYZ(float angle);

    Mat3 rotatedZX(float angle);

    Mat3 scaled(float xs, float ys, float zs);

    Mat2 mat2();

    union
    {
        struct
        {
            float e11;
            float e12;
            float e13;
            float e21;
            float e22;
            float e23;
            float e31;
            float e32;
            float e33;
        };
        float data[9];
    };
};

Mat3 operator+(Mat3 a, Mat3 const &b);

Mat3 operator-(Mat3 a, Mat3 const &b);

Mat3 operator*(Mat3 const &a, Mat3 const &b);

struct Mat4
{
    Mat4() = default;

    Mat4(Mat4 const &) = default;

    explicit Mat4(Mat3 const&);
    explicit Mat4(Mat2 const&);

    Mat4 &operator=(Mat4 const &) = default;

    Mat4(float e11, float e12, float e13, float e14,
         float e21, float e22, float e23, float e24,
         float e31, float e32, float e33, float e34,
         float e41, float e42, float e43, float e44);

    explicit Mat4(float s);

    Mat4 &operator+=(Mat4 const &m);

    Mat4 &operator-=(Mat4 const &m);

    Mat4 &operator*=(Mat4 const &m);

    float &operator[](int i);

    float const &operator[](int i) const;

    Mat4 rotatedXY(float angle);

    Mat4 rotatedYZ(float angle);

    Mat4 rotatedZX(float angle);

    Mat4 scaled(float xs, float ys, float zs);

    Mat4 translated(float xt, float yt, float zt);

    Mat4 perspective(float xnear, float ynear, float near, float far);

    Mat4 ortho(float top, float bottom, float left, float right, float near, float far);

    Mat3 mat3();

    Mat2 mat2();

    union
    {
        struct
        {
            float e11;
            float e12;
            float e13;
            float e14;
            float e21;
            float e22;
            float e23;
            float e24;
            float e31;
            float e32;
            float e33;
            float e34;
            float e41;
            float e42;
            float e43;
            float e44;
        };
        float data[16];
    };
};

Mat4 operator+(Mat4 a, Mat4 const &b);

Mat4 operator-(Mat4 a, Mat4 const &b);

Mat4 operator*(Mat4 const &a, Mat4 const &b);

#endif //CITS3003_MAT_H
