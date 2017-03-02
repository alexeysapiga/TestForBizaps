#include "Line.h"


Line::Line(const Vector3& pos, const Vector3& dir, float length) {
    direction_ = dir;
    length_ = length;
    position_ = pos;
}

void Line::draw() {
    glPushMatrix();
    glLineWidth(2.5f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(position_.x, position_.y, position_.z);
    glVertex3f(position_.x + length_ * direction_.x,
        position_.y + length_ * direction_.y,
        position_.z + length_ * direction_.z);
    glEnd();
    glPopMatrix();
}
