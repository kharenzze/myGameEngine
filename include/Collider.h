//
// Created by Paolo on 23/02/2018.
//

#ifndef MYGAMEENGINE_COLLIDER_H
#define MYGAMEENGINE_COLLIDER_H

#include "Transform.h"
#include "glm/glm.hpp"


class Collider {
public:
    virtual bool checkCollision(const Collider& other) const = 0;
    virtual bool collisionWithPoint(const glm::vec3& p) const = 0;
    glm::vec3 center;
};


#endif //MYGAMEENGINE_COLLIDER_H
