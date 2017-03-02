#include "Time.h"
#include <glut.h>

float Time::deltaTime_ = 0.0f;

Time::Time() {
    timePrev_ = glutGet(GLUT_ELAPSED_TIME);
}

float Time::getDeltaTime() {
    return deltaTime_;
}

void Time::udateTime() {
    int   timeNow = glutGet(GLUT_ELAPSED_TIME);

    deltaTime_ = float(timeNow - timePrev_) / 1000.0f;

    timePrev_ = timeNow;
}