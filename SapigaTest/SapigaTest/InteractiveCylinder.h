#ifndef INTERACTIVE_CYLINDER_H
#define INTERACTIVE_CYLINDER_H

#include "Engine/GameObject.h"
#include "Engine/Cylinder.h"

class InteractiveCylinder : public GameObject {
public:
    InteractiveCylinder(Cylinder* cylinder);
    ~InteractiveCylinder();
    virtual void update();
    virtual void draw();
    virtual Collider* getCollider();
private:
    void (InteractiveCylinder::*updateMethod_)();
    void updateMouse();
    void updatePhysicsForce();
    void updatePhysicsRungeKutta();
    void updatePhysicsAnalytic();
    void calculateOrientation();

    Cylinder* cylinder_;

    float springConstant_;
    float viscousDamp_;
    float mass_;

    float angleFi_;
    float angleTeta_;
    float angleStart_;
    float time_;
    float savedAngleFi_;
    float savedAngleTeta_;
    float velocity_;

    bool pressed_ = false;
    bool simulatePhysics_;
    Vector3 savedPosition_;
};

#endif
