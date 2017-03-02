#include "CylinderCollider.h"


CylinderCollider::CylinderCollider(float radius, float height) {
    height_ = height;
    radius_ = radius;
}

ColliderType CylinderCollider::getType() {
    return ColliderType::COLLIDER_CYLINDER;
}

const Vector3& CylinderCollider::getPosition() { 
    return holder_->getPosition();
}

const Vector3& CylinderCollider::getOrientation() { 
    return holder_->getOrientation();
}

float CylinderCollider::getRadius() {
    return radius_; 
}

float CylinderCollider::getHeight() { 
    return height_;
}