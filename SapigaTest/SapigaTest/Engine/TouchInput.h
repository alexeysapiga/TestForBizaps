#ifndef TOUCH_INPUT_H
#define TOUCH_INPUT_H

#include "Math/Vector3.h"

enum TouchState {
    TOUCH_DOWN,
    TOUCH_MOVE,
    TOUCH_UP
};

class TouchInput {
public:
    static TouchInput* instance();
    void processPress(int button, int state, int x, int y);
    void processMove(int x, int y);
    int getButton();
    Vector3 getPosition();
    TouchState getState();
private:
    static TouchInput* instance_;
    Vector3 position_;
    int button_;
    TouchState state_;
};

#endif