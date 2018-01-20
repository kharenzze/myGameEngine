//
// Created by Paolo on 20/01/2018.
//

#ifndef MYGAMEENGINE_CAMERA_H
#define MYGAMEENGINE_CAMERA_H

#include <glm/glm.hpp>

#include "Utils.h"

const glm::vec3 cameraFront = -FRONT;
const glm::vec3 cameraUp = UP;
const glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));

class Camera {
public:
    Camera();
    Camera(const float speed, const glm::vec3 &pos);
    glm::mat4 getViewMatrix() const;

    glm::vec3 pos;
    float speed;
};


#endif //MYGAMEENGINE_CAMERA_H
