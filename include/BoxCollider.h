//
// Created by Paolo on 23/02/2018.
//

#ifndef MYGAMEENGINE_BOXCOLLIDER_H
#define MYGAMEENGINE_BOXCOLLIDER_H

#include "Collider.h"
#include <glm/glm.hpp>


class BoxCollider : public Collider {
public:
    bool checkCollision(const Collider& other) const override;
    bool collisionWithPoint(const glm::vec3& p) const override;
    float radius;

    BoxCollider();
};


#endif //MYGAMEENGINE_BOXCOLLIDER_H
