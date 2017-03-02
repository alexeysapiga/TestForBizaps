#ifndef CYLINDER_COLLIDER_H
#define CYLINDER_COLLIDER_H

#include "Collider.h"

class CylinderCollider : public Collider {
public:
    CylinderCollider(float radius, float height);
    virtual ColliderType getType();
    const Vector3& getPosition();
    const Vector3& getOrientation();
    float getRadius();
    float getHeight();
private:
    float height_;
    float radius_;
};

#endif