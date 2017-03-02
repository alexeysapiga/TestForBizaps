#include "Vector3.h"

const Vector3 Vector3::up_ = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::right_ = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::forward_ = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::one_ = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::zero_ = Vector3(0.0f, 0.0f, 0.0f);

Vector3::Vector3() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Vector3::Vector3(float ix, float iy, float iz) {
    x = ix;
    y = iy;
    z = iz;
}

float Vector3::dot(const Vector3& vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::cross(const Vector3& vec) const {
    Vector3 result;
    result.x = y * vec.z - z * vec.y;
    result.y = -x * vec.z + z * vec.x;
    result.z = x * vec.y - y * vec.x;
    return result;
}

Vector3 Vector3::normalized() const {
    float length = sqrt(x * x + y * y + z * z);
    return Vector3(x / length, y / length, z / length);
}

float Vector3::length() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::operator* (float k) const {
    Vector3 result;
    result.x = k * x;
    result.y = k * y;
    result.z = k * z;
    return result;
}

Vector3 Vector3::operator/ (float k) const {
    Vector3 result;
    result.x = x / k;
    result.y = y / k;
    result.z = z / k;
    return result;
}

Vector3 Vector3::operator - (const Vector3& vec) const {
    Vector3 result;
    result.x = x - vec.x;
    result.y = y - vec.y;
    result.z = z - vec.z;
    return result;
}

Vector3 Vector3::operator + (const Vector3& vec) const {
    Vector3 result;
    result.x = x + vec.x;
    result.y = y + vec.y;
    result.z = z + vec.z;
    return result;
}