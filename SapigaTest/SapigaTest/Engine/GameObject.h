#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Math/Vector3.h"
#include <glut.h> 
#include "Collider.h"
class Collider;

class GameObject {
public:
	GameObject();
	virtual ~GameObject();
    virtual void draw();
    virtual void update();
    const Vector3& getPosition();
    virtual void setPosition(const Vector3& position);
    const Vector3& getOrientation();
    virtual void setOrientation(const Vector3& orientation);
    void setCollider(Collider* collider);
    virtual Collider* getCollider();
protected:
    Vector3 position_;
    Vector3 orientation_;
    Collider* collider_;
};

#endif