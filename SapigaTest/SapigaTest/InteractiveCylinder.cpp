#include "InteractiveCylinder.h"
#include "Engine/Engine.h"

const float MOUSE_COEFFICIENT = 0.01f;
const float ANGLE_MAXIMUM = 1.0f;

const char* RUNGE_KUTTA = "RungeKutta";
const char* FORCE = "Force";
const char* ANALYTIC = "Analytic";

InteractiveCylinder::InteractiveCylinder(Cylinder* cylinder) {
    cylinder_ = cylinder;

    velocity_ = 0.0f;
    angleFi_ = 0.0f;
    angleTeta_ = 0.0f;
    angleStart_ = 0.0f;
    time_ = 0.0f;
    savedAngleFi_ = 0.0f;
    savedAngleTeta_ = 0.0f;
    simulatePhysics_ = false;
    pressed_ = false;
    savedPosition_ = Vector3::zero_;

    springConstant_ = ApplicationSettings::instance()->getFloat("spring_constant", 10.0f);
    viscousDamp_ = ApplicationSettings::instance()->getFloat("viscous_damp", 1.0f);
    mass_ = ApplicationSettings::instance()->getFloat("mass", 1.0f);

    string simulationsType = ApplicationSettings::instance()->getString("simulations_type", RUNGE_KUTTA);
    if (simulationsType == RUNGE_KUTTA)
        updateMethod_ = &InteractiveCylinder::updatePhysicsRungeKutta;
    else if (simulationsType == FORCE)
        updateMethod_ = &InteractiveCylinder::updatePhysicsForce;
    else 
        updateMethod_ = &InteractiveCylinder::updatePhysicsAnalytic;
}

InteractiveCylinder::~InteractiveCylinder() {
    delete cylinder_;
}

void InteractiveCylinder::update() {
    cylinder_->update();
    updateMouse();
    (this->*updateMethod_)();
}

void InteractiveCylinder::draw() {
    cylinder_->draw();
}

Collider* InteractiveCylinder::getCollider() {
    return cylinder_->getCollider();
}

void InteractiveCylinder::updatePhysicsForce() {
    if (!simulatePhysics_) return;

    float k0 = springConstant_ / mass_;
    float c0 = viscousDamp_ / (2.0f * mass_);

    float dt = Time::getDeltaTime();
    angleFi_ += velocity_ * dt;
    velocity_ += (-velocity_ * c0 - k0 * angleFi_) * dt / mass_;
    calculateOrientation();
}


void InteractiveCylinder::updatePhysicsRungeKutta() {
    if (!simulatePhysics_) return;

    float k0 = springConstant_ / mass_;
    float c0 = viscousDamp_ / (2.0f * mass_);

    float dt = Time::getDeltaTime();
    float kx0 = dt * velocity_;
    float kv0 = dt * (-k0 * angleFi_ - c0 * velocity_);
    float kx1 = dt * (velocity_ + kv0 * 0.5f);
    float kv1 = dt * (-k0 * (angleFi_ + 0.5f * kx0) - c0 * (velocity_ + kv0 * 0.5f));
    float kx2 = dt * (velocity_ + 0.5f * kv1);
    float kv2 = dt * (-k0 * (angleFi_ + 0.5f * kx1) - c0 * (velocity_ + 0.5f * kv1));
    float kx3 = dt * (velocity_ + 0.5f * kv2);
    float kv3 = dt * (-k0 * (angleFi_ + 0.5f * kx2) - c0 * (velocity_ + 0.5f * kv2));

    angleFi_ += (kx0 + 2.0f * kx1 + 2.0f * kx2 + kx3) / 6.0f;
    velocity_ += (kv0 + 2.0f * kv1 + 2.0f * kv2 + kv3) / 6.0f;
    calculateOrientation();
}


void InteractiveCylinder::updatePhysicsAnalytic() {
    if (!simulatePhysics_) return;

    float w02 = springConstant_ / mass_;
    float b = viscousDamp_ / (2.0f * mass_);
    float wd = sqrt(w02 - b * b);

    angleFi_ = exp(-b * time_) * angleStart_ * cos(wd * time_);
    calculateOrientation();
    time_ += Time::getDeltaTime();
}


void InteractiveCylinder::updateMouse() {
    if (TouchInput::instance()->getButton() != 0) return;

    if (TouchInput::instance()->getState() == TOUCH_DOWN) {
        if (pressed_) return;
        
        savedPosition_ = TouchInput::instance()->getPosition();
        auto ray = Camera::screenPointToRay(savedPosition_);
        pressed_ = RayCast::cylinderCast(ray);

        if (pressed_)  {
            savedAngleFi_ = angleFi_;
            savedAngleTeta_ = angleTeta_;
            simulatePhysics_ = false;
        }
        
    }
    else if (TouchInput::instance()->getState() == TOUCH_MOVE && pressed_) {
        Vector3 diff = TouchInput::instance()->getPosition() - savedPosition_;
        angleFi_ = savedAngleFi_ + diff.y * MOUSE_COEFFICIENT;
        angleTeta_ = savedAngleTeta_ + diff.x * MOUSE_COEFFICIENT;
        if (fabs(angleFi_) > ANGLE_MAXIMUM)
        {
            angleFi_ = ANGLE_MAXIMUM * angleFi_ / fabs(angleFi_);
        }
        calculateOrientation();
    }
    else {
        if (pressed_) {
            simulatePhysics_ = true;
            angleStart_ = angleFi_;
            time_ = 0.0f;
            velocity_ = 0.0f;
        }

        pressed_ = false;
    }
}

void InteractiveCylinder::calculateOrientation() {
    cylinder_->setOrientation(Vector3(sin(angleFi_) * cos(angleTeta_), sin(angleFi_) * sin(angleTeta_), cos(angleFi_)));
}
