#ifndef RAY_CAST_H
#define RAY_CAST_H

#include "Vector3.h"

struct Ray {
    Vector3 startPoint_;
    Vector3 direction_;
    Ray(){
        startPoint_ = Vector3::zero_;
        direction_ = Vector3::zero_;
    }

    Ray(const Vector3& startPos, const Vector3& direction){
        startPoint_ = startPos;
        direction_ = direction.normalized();
    }
};

class RayCast {
public:
    static bool cylinderCast(const Vector3 startPoint, const Vector3& direction);
    static bool cylinderCast(Ray ray);
};

#endif