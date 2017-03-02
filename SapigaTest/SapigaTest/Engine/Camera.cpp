#include "Camera.h"
#include "TouchInput.h"
#include "Core.h"
#include "Math/Matrix.h"
#include "Line.h"

Camera::Camera(float fov, float z_near, float z_far) {
    mousePressed_ = false;
    angleXy_ = 0.0f;
    savedAngleXy_ = 0.0f;
    radius_ = 0.0f;

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)Core::instance()->getWidth() / (float)Core::instance()->getHeight();
    gluPerspective(fov, aspect, z_near, z_far);
}

void Camera::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(radius_ * cos(angleXy_), radius_ * sin(angleXy_), position_.z, 0, 0, 0, 0, 0, 1);
}


void Camera::update() {
    auto touch = TouchInput::instance();
    if (touch->getButton() == 2 && touch->getState() == TOUCH_DOWN) {
        mousePressed_ = true;
        positionTouch_ = TouchInput::instance()->getPosition();
        savedAngleXy_ = angleXy_;
    }
    else if (touch->getButton() == 2 && touch->getState() == TOUCH_MOVE && mousePressed_) {
       
        float dv = (TouchInput::instance()->getPosition().x - positionTouch_.x);

        angleXy_ = savedAngleXy_ + dv * 0.01;
    }
    else {
        mousePressed_ = false;
    }
}

void Camera::setPosition(const Vector3& position) {
    radius_ = sqrt(position.x*position.x + position.y*position.y);
    position_ = position;
}

Vector3 Camera::screenPointToWorld(const Vector3& pos) {
    GLdouble proj[16];
    glGetDoublev(GL_PROJECTION_MATRIX, proj);

    GLdouble modelView[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
    GLint port[4];
    glGetIntegerv(GL_VIEWPORT, port);
    
    double x, y, z;
    gluUnProject(pos.x, port[2] - pos.y, pos.z, modelView, proj, port, &x, &y, &z);

    return Vector3(x, y, z);
}

Ray Camera::screenPointToRay(const Vector3& pos) {
    GLdouble proj[16];
    glGetDoublev(GL_PROJECTION_MATRIX, proj);

    GLdouble modelView[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelView);

    GLint port[4];
    glGetIntegerv(GL_VIEWPORT, port);
    
    double x, y, z;
    gluUnProject(pos.x, port[3] - pos.y, 0.0f, modelView, proj, port, &x, &y, &z);
    double xf, yf, zf;
    gluUnProject(pos.x, port[3] - pos.y, 1.0f, modelView, proj, port, &xf, &yf, &zf);

    return Ray(Vector3(x, y, z), Vector3(xf - x, yf - y, zf - z));
}