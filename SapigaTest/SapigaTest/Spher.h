#pragma once
#include "Engine\Engine.h"
class Spher :
    public GameObject
{
public:
    Spher();
    ~Spher();
    virtual void draw();
    virtual void update();
};

