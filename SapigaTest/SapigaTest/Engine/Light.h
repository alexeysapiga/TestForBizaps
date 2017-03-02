#ifndef LIGHT_H
#define LIGHT_h

#include "GameObject.h"

class Light : public GameObject {
public:
    Light();
    ~Light();
    virtual void setPosition(const Vector3& pos);
private:
    static int lightIndex_;
    int currentLightIndex_;
};
#endif
