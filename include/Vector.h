 #pragma once
 #include <math.h>
 #include <stdio.h>
 #include <string>

typedef float real;
using namespace std;

class Vector3
{
    public:
        Vector3();
        Vector3(real x, real y, real z);
        real x;
        real y;
        real z;

        Vector3 operator+(const Vector3& v);
        Vector3 operator-(const Vector3& v);
        Vector3 operator*(const Vector3& v);
        Vector3 operator*(const real& scalar);
        Vector3 operator/(const Vector3& v);
        Vector3 operator/(const real& v);
        Vector3 projectOn(Vector3 v);
        Vector3 normalized();
        real getDistance(const Vector3& v);
        real magnitude();
        real dot(Vector3 other);
        string toString();
        void normalize();
};

class Vector2
{
    public:
        Vector2();
        Vector2(real x, real y);
        real x;
        real y;

        Vector2 operator+(const Vector2& v);
        Vector2 operator-(const Vector2& v);
        Vector2 operator*(const Vector2& v);
        Vector2 operator*(const real& scalar);
        Vector2 operator/(const Vector2& v);
        Vector2 operator/(const real& v);
        Vector2 projectOn(Vector2 v);
        Vector2 normalized();
        real getDistance(const Vector2& v);
        real magnitude();
        real dot(Vector2 other);
        string toString();
        void normalize();
        void rotate(real angle);
};