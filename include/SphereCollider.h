//
// Created by Paolo on 23/02/2018.
//

#ifndef MYGAMEENGINE_SPHERECOLLIDER_H
#define MYGAMEENGINE_SPHERECOLLIDER_H

#include "Collider.h"
#include <glm/glm.hpp>

class SphereCollider : public Collider {
public:
    bool checkCollision(const Collider& other) const override;
    bool collisionWithPoint(const glm::vec3& p) const override;
    float radius;
    SphereCollider();
};


#endif //MYGAMEENGINE_SPHERECOLLIDER_H
