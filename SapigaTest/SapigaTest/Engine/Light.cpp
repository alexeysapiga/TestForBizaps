#include "Light.h"

int Light::lightIndex_ = GL_LIGHT0;

Light::Light() {
    currentLightIndex_ = lightIndex_;
    lightIndex_++;

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(currentLightIndex_, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(currentLightIndex_);
    glEnable(GL_DEPTH_TEST);
}

void Light::setPosition(const Vector3& pos) {
    GameObject::setPosition(pos);
    GLfloat light_position[] = { pos.x, pos.y, pos.z, 0.0f };
    glLightfv(currentLightIndex_, GL_POSITION, light_position);
}

Light::~Light() {
    glDisable(currentLightIndex_);
    lightIndex_--;
    if (lightIndex_ < GL_LIGHT0)
        glDisable(GL_LIGHTING);
}
