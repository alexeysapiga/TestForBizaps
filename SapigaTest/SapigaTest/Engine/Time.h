#pragma once

#include <time.h>

class Time {
public:
    Time();
    static float getDeltaTime();
    void udateTime();
private:
    static float deltaTime_; 
    int  timePrev_;
};

