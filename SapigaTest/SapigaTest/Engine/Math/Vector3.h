#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float ix, float iy, float iz);

    float dot (const Vector3& vec) const;
    Vector3 cross(const Vector3& vec) const;
    Vector3 normalized() const;
    float length() const;

    Vector3 operator- (const Vector3& vec) const;
    Vector3 operator+ (const Vector3& vec) const;
    Vector3 operator* (float k) const;
    Vector3 operator/ (float k) const;
    
    static const Vector3 up_;
    static const Vector3 right_;
    static const Vector3 forward_;
    static const Vector3 one_;
    static const Vector3 zero_;
};

#endif