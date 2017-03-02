#ifndef LINE_H
#define LINE_H

#include "GameObject.h"

class Line : public GameObject {
public:
    Line(const Vector3& pos, const Vector3& dir, float length);
    
    virtual void draw();
private:
    Vector3 direction_;
    float length_;
};

#endif