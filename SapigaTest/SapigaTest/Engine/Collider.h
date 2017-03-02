#ifndef COLLIDER_H
#define COLLIDER_H
#include "GameObject.h"

enum class ColliderType {
    COLLIDER_CYLINDER
};

class GameObject;

class Collider {
public:
    virtual ~Collider();
    virtual ColliderType getType() = 0;
    virtual const Vector3& getPosition() = 0;
    virtual const Vector3& getOrientation() = 0;
protected:
    Collider(){}
    GameObject* holder_;
    friend class GameObject;
};

#endif