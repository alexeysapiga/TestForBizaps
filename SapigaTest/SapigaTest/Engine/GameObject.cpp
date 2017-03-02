#include "GameObject.h"


GameObject::GameObject() {
    collider_ = 0;
}


GameObject::~GameObject() {
    if (collider_ != 0)
        delete collider_;
}

void GameObject::draw() {
}

void GameObject::update() {
}

const Vector3& GameObject::getPosition() {
    return position_; 
}

void GameObject::setPosition(const Vector3& position) {
    position_ = position;
}

const Vector3& GameObject::getOrientation() {
    return orientation_;
}

void GameObject::setOrientation(const Vector3& orientation) {
    orientation_ = orientation;
}

void GameObject::setCollider(Collider* collider) {
    collider_ = collider;
    collider_->holder_ = this;
}

Collider* GameObject::getCollider() {
    return collider_;
}