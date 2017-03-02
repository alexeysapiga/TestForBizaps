#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Math/RayCast.h"


class Camera : public GameObject {
public:
    Camera(float fov, float zNear, float zFa);

    virtual void draw();
    virtual void update();
    virtual void setPosition(const Vector3& position);

    static Vector3 screenPointToWorld(const Vector3& pos);
    static Ray screenPointToRay(const Vector3& pos);
private:
    bool mousePressed_;
    Vector3 positionTouch_;
    float angleXy_;
    float savedAngleXy_;
    float radius_;
};
#endif
