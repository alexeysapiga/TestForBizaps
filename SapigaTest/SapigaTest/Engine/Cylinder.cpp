#include "Cylinder.h"

const int kSlices = 32;
const int kStacks = 32;

Cylinder::Cylinder(float radius, float height) {
    radius_ = radius;
    height_ = height;

    orientation_ = Vector3(0.0f, 0.0f, 1.0f).normalized();
    quadric_ = gluNewQuadric();
}

Cylinder::~Cylinder() {
    delete quadric_;
}

void Cylinder::draw() {
    glPushMatrix();

    matrix_.translate(position_);
    matrix_.lookAt(Vector3::forward_, orientation_, Vector3::up_);
    glMultMatrixf(matrix_.getMatrix());

    gluCylinder(quadric_, radius_, radius_, height_, kSlices, kStacks);

    glPopMatrix();
}

float Cylinder::getRadius() {
    return radius_;
}

float Cylinder::getHeight() {
    return height_; 
}