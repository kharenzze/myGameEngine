//
// Created by Paolo on 23/02/2018.
//

#include "Ball.h"
#include <math.h>

Ball::Ball() {
    speed = 1;
    dir = glm::normalize(glm::vec3(1, 2, 0));
}

void Ball::onCollision(const Collider *other) {
    auto inv = glm::normalize(collider->center - other->center);
    auto x = glm::dot(inv, glm::vec3(1,0,0));
    auto y = glm::dot(inv, glm::vec3(0,1,0));
    glm::vec3 norm;
    if (fabs(x) > fabs(y)) {
        norm = glm::normalize(glm::vec3(1,0,0) * x);
    } else {
        norm = glm::normalize(glm::vec3(0,1,0) * y);
    }
    dir = glm::reflect(dir, norm);
}

void Ball::move(float dt) {
    const auto npos = transform.getPosition() + (dir * speed * dt);
    transform.setPosition(npos);
    collider->center = npos;
}