//
// Created by Paolo on 23/02/2018.
//

#ifndef MYGAMEENGINE_BALL_H
#define MYGAMEENGINE_BALL_H

#include <glm/glm.hpp>
#include "GameObject.h"
#include "Collider.h"


class Ball : public GameObject {
public:
    void onCollision(const Collider *other);
    void move(float dt);
    glm::vec3 dir;
    float speed;
    Ball();
};


#endif //MYGAMEENGINE_BALL_H
