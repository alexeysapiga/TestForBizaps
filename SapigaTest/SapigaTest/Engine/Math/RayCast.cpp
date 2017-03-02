#include "RayCast.h"
#include "../Core.h"
#include "../Cylinder.h"
#include "../CylinderCollider.h"

bool RayCast::cylinderCast(const Vector3 startPoint, const Vector3& direction) {
    auto objects = Core::instance()->getElements();
    size_t size = objects.size();
    for (size_t i = 0; i < size; i++)
    {
        auto collider = objects[i]->getCollider();
        if (collider == 0 || collider->getType() != ColliderType::COLLIDER_CYLINDER) continue;

        auto colliderCyl = dynamic_cast<CylinderCollider*>(collider);
        if (colliderCyl == 0) continue; 

        Vector3 va1 = collider->getOrientation().normalized();
        Vector3 va(va1.x, va1.y, va1.z);
        Vector3 pa = collider->getPosition();
        Vector3 dp = startPoint - pa;
        Vector3 dA = direction - (va * direction.dot(va));
        float A = dA.dot(dA);

        float B = 2.0f *(direction - (va * direction.dot(va))).dot(dp - va * dp.dot(va));
        Vector3 dC = dp - va * dp.dot(va);
        float C = dC.dot(dC) - colliderCyl->getRadius() * colliderCyl->getRadius();
        float D = B * B - 4 * A * C;

        if (D < 0.0f) continue;
        float t1 = (-B + sqrt(D)) / (2 * A);
        float t2 = (-B - sqrt(D)) / (2 * A);

        if (t1 < 0.0f || t2 < 0.0f) continue;

        Vector3 p1 = colliderCyl->getPosition();
        Vector3 p2 = colliderCyl->getPosition() + va.normalized() * colliderCyl->getHeight();
        Vector3 q1 = startPoint + direction * t1;
        Vector3 q2 = startPoint + direction * t2;
        
        if (va.dot(q1 - p1) < 0.0f || va.dot(q2 - p2) > 0.0f) continue;
        return true;
    }
    return false;
}


bool RayCast::cylinderCast(Ray ray) {
    return cylinderCast(ray.startPoint_, ray.direction_);
}