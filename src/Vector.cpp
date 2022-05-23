#include "Vector.h"

//Vector3
Vector3::Vector3()
{
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}
Vector3::Vector3(real x, real y, real z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3 Vector3::operator+(const Vector3& v)
{
    return Vector3(this->x+v.x,this->y+v.y,this->z+v.z);
}


Vector3 Vector3::operator-(const Vector3& v)
{
    return Vector3(this->x-v.x,this->y-v.y,this->z-v.z);
}
Vector3 Vector3::operator*(const Vector3& v)
{
    return Vector3(this->x*v.x,this->y*v.y,this->z*v.z);
}
Vector3 Vector3::operator*(const real& scalar)
{
    return Vector3(this->x*scalar,this->y*scalar,this->z*scalar);
}
Vector3 Vector3::operator/(const Vector3& v)
{
    return Vector3(this->x/v.x, this->y/v.y, this->z/v.z);
}
Vector3 Vector3::operator/(const real& v)
{
    return Vector3(this->x/v, this->y/v, this->z/v);
}
Vector3 Vector3::normalized()
{
    real mag = this->magnitude();
    return Vector3(this->x / mag, this->y / mag, this->z / mag);
}
Vector3 Vector3::projectOn(Vector3 v)
{
    Vector3 normV = v.normalized();
    real mag = v.magnitude();
    return normV*(normV.dot(*this)*mag);
}
real Vector3::getDistance(const Vector3& v)
{
    Vector3 diff = *this - v;
    return sqrt(diff.magnitude());
}
real Vector3::magnitude()
{
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}
real Vector3::dot(Vector3 other)
{
    return (x*other.x + y*other.y + z*other.z);
}
string Vector3::toString()
{
    char str[30];
    sprintf(str, "X:%f Y:%f Z:%f", x, y, z);
    return string(str);
}
void Vector3::normalize()
{
    real mag = this->magnitude();
    this->x = this->x / mag;
    this->y = this->y / mag;
    this->z = this->z / mag;
}

//Vector2
Vector2::Vector2()
{
    this->x = 0.0f;
    this->y = 0.0f;
}
Vector2::Vector2(real x, real y)
{
    this->x = x;
    this->y = y;
}

Vector2 Vector2::operator+(const Vector2& v)
{
    return Vector2(this->x+v.x,this->y+v.y);
}


Vector2 Vector2::operator-(const Vector2& v)
{
    return Vector2(this->x-v.x,this->y-v.y);
}
Vector2 Vector2::operator*(const Vector2& v)
{
    return Vector2(this->x*v.x,this->y*v.y);
}
Vector2 Vector2::operator*(const real& scalar)
{
    return Vector2(this->x*scalar,this->y*scalar);
}
Vector2 Vector2::operator/(const Vector2& v)
{
    return Vector2(this->x/v.x, this->y/v.y);
}
Vector2 Vector2::operator/(const real& v)
{
    return Vector2(this->x/v, this->y/v);
}
Vector2 Vector2::normalized()
{
    real mag = this->magnitude();
    return Vector2(this->x / mag, this->y / mag);
}
Vector2 Vector2::projectOn(Vector2 v)
{
    Vector2 normV = v.normalized();
    real mag = v.magnitude();
    return normV*(normV.dot(*this)*mag);
}
real Vector2::getDistance(const Vector2& v)
{
    Vector2 diff = *this - v;
    return sqrt(diff.magnitude());
}
real Vector2::magnitude()
{
    return sqrt(this->x*this->x + this->y*this->y);
}
real Vector2::dot(Vector2 other)
{
    return (x*other.x + y*other.y);
}
string Vector2::toString()
{
    char str[30];
    sprintf(str, "X:%f Y:%f", x, y);
    return string(str);
}
void Vector2::normalize()
{
    real mag = this->magnitude();
    this->x = this->x / mag;
    this->y = this->y / mag;
}
void Vector2::rotate(real angle)
{
    float x = cos(angle)*this->x - sin(angle)*this->y;
    float y = sin(angle)*this->x + cos(angle)*this->y;
    this->x = x;
    this->y = y;
}