#include "TouchInput.h"

TouchInput* TouchInput::instance_ = 0;

TouchInput* TouchInput::instance() {
    if (instance_ == 0)
        instance_ = new TouchInput();

    return instance_;
}

int TouchInput::getButton() {
    return button_; 
}

Vector3 TouchInput::getPosition() {
    return position_;
}

TouchState TouchInput::getState() {
    return state_; 
}

void TouchInput::processPress(int button, int state, int x, int y) {
    button_ = button;
    state_ = (state == 0) ? TOUCH_DOWN : TOUCH_UP;
    position_ = Vector3(x, y, 0.0f);
}

void TouchInput::processMove(int x, int y) {
    position_ = Vector3(x, y, 0.0f);
    state_ = TOUCH_MOVE;
}

