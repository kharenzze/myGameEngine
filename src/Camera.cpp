//
// Created by Paolo on 20/01/2018.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera() {
    this->speed = 2.0f;
    this->pos = glm::vec3(0);
}

Camera::Camera(const float speed, const glm::vec3 &pos) {
    this->speed = speed;
    this->pos = pos;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(this->pos,
                this->pos - cameraFront,
                cameraUp);
}