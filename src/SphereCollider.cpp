//
// Created by Paolo on 23/02/2018.
//

#include "SphereCollider.h"
#include "Utils.h"

using glm::vec3;

SphereCollider::SphereCollider() {
    radius = 0;
    center = ZERO3;
}

bool SphereCollider::collisionWithPoint(const glm::vec3& p) const {
    return glm::distance(center, p) <= radius;
}

bool SphereCollider::checkCollision(const Collider &other) const {
    const auto dir = glm::normalize(other.center - center);
    const auto border = center + (dir * radius);
    return other.collisionWithPoint(border);
}
