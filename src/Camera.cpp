//
// Created by Paolo on 20/01/2018.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include <glm/gtc/constants.hpp>


using glm::vec3;
using glm::radians;

constexpr float MAX_PITCH = 89.0f;
constexpr float MIN_PITCH = -89.0f;
const vec3 DEFAULT_ROTATION = vec3(0, -90, 0);

Camera::Camera() {
    this->speed = 2.0f;
    this->pos = ZERO3;
    this->fov = 45.0f;
    setRotation(DEFAULT_ROTATION);
}

Camera::Camera(const float speed, const vec3 &pos, const float fov = 45.0f) {
    this->speed = speed;
    this->pos = pos;
    this->fov = fov;
    setRotation(DEFAULT_ROTATION);
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(pos,
                pos - _front,
                cameraUp);
}

float Camera::getFov() const {
    return fov;
}

void Camera::setFov(float fov) {
    if (fov >= 1 && fov <= 45) {
        this->fov = fov;
    }
}

void Camera::moveFov(float offset) {
    setFov(offset + fov);
}

void Camera::setRotation(const vec3 &rotation) {
    _rotation = rotation;
    _adjustRotation();
    _calculateFront();
}

void Camera::addRotation(const vec3 &dRotation) {
    _rotation += dRotation;
    _adjustRotation();
    _calculateFront();
}

void Camera::_adjustRotation() {
    if (_rotation[0] > MAX_PITCH) {
        _rotation[0] = MAX_PITCH;
    } else if (_rotation[0] < MIN_PITCH) {
        _rotation[0] = MIN_PITCH;
    }
}

glm::vec3 Camera::getFront() const{
    return _front;
}

void Camera::_calculateFront() {
    _front.x = cos(radians(_rotation.y)) * cos(radians(_rotation.x));
    _front.y = sin(radians(_rotation.x));
    _front.z = sin(radians(_rotation.y)) * cos(radians(_rotation.x));
    _front = glm::normalize(_front);
}

glm::vec3 Camera::getRight() const {
    return glm::cross(_front, UP);
}

glm::vec3 Camera::getFPSFront() const {
    return glm::normalize(vec3(_front.x, 0, _front.z));
}

glm::vec3 Camera::getFPSRight() const {
    return glm::cross(getFPSFront(), UP);
}