#ifndef CYLINDER_H
#define CYLINDER_H

#include "GameObject.h"
#include "Math/Matrix.h"

class Cylinder : public GameObject {
public:
    Cylinder(float radius, float height);
    ~Cylinder();
    virtual void draw();
    float getRadius();
    float getHeight();

private:
    GLUquadric* quadric_;
    
    float radius_;
    float height_;
    Matrix matrix_;
};

#endif