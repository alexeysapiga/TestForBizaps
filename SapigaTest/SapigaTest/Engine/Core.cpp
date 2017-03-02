#include "Core.h"
#include <algorithm>

Core* Core::instance_ = 0;

Core* Core::instance() {
    if (instance_ == 0)
        instance_ = new Core();

    return instance_; 
}

const vector<GameObject*>& Core::getElements() {
    return activeObjects_; 
}

void Core::setResolution(int width, int height) {
    width_ = width;
    height_ = height;
}

float Core::getWidth() {
    return width_;
}

float Core::getHeight() {
    return height_;
}

void Core::draw() {
    size_t size = activeObjects_.size();
    for (size_t i = 0; i < size; i++)
        activeObjects_[i]->draw();

    glutSwapBuffers();
}

void Core::update() {
    size_t size = activeObjects_.size();
    for (size_t i = 0; i < size; i++)
        activeObjects_[i]->update();

    destroyObjects();
    timer_.udateTime();
}

void Core::add(GameObject* go) {
    activeObjects_.push_back(go);
}

void Core::destroy(GameObject* go) {

    objectsToDestroy_.push_back(go);
}

void Core::destroyObjects() {
    size_t size = objectsToDestroy_.size();
    for (size_t i = 0; i < size; i++){
        auto it = find(activeObjects_.begin(), activeObjects_.end(), objectsToDestroy_[i]);
        activeObjects_.erase(it);
        delete objectsToDestroy_[i];
    }

    objectsToDestroy_.clear();
}

Core::Core() {

}

Core::~Core() {
    size_t size = activeObjects_.size();
    for (size_t i = 0; i < size; i++)
        delete activeObjects_[i];
}
