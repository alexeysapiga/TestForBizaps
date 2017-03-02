#include "Engine/Engine.h"
#include "Game.h"
#include "InteractiveCylinder.h"
#include "MassSystem.h"
#include "Spher.h"

Game::Game() {
    ApplicationSettings* settings = ApplicationSettings::instance();

    auto camera = new Camera(settings->getFloat("field_of_view"), settings->getFloat("z_near"), settings->getFloat("z_far"));
    camera->setPosition(settings->getVector3("position_camera"));

    auto light = new Light();
    light->setPosition(settings->getVector3("position_light"));

   /* float radius = settings->getFloat("radius");
    float height = settings->getFloat("height");
    auto cylinder = new Cylinder(radius, height);
    cylinder->setPosition(settings->getVector3("position_cylinder"));
    
    cylinder->setCollider(new CylinderCollider(radius, height));*/

    Core::instance()->add(camera);
    Core::instance()->add(light);
    //Core::instance()->add(new InteractiveCylinder(cylinder));

    Core::instance()->add(new MassSystem());
}