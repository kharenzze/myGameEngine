//
// Created by Paolo on 23/02/2018.
//

#include "BoxCollider.h"
#include "Utils.h"

BoxCollider::BoxCollider() {
    radius = 0;
    center = ZERO3;
}

bool BoxCollider::collisionWithPoint(const glm::vec3& p) const {
    return p.x >= (center.x - radius) && p.x <= (center.x + radius) &&
           p.y >= (center.y - radius) && p.y <= (center.y + radius) &&
           p.z >= (center.z - radius) && p.z <= (center.z + radius);
}

bool BoxCollider::checkCollision(const Collider &other) const {
    //TODO
    return false;
}