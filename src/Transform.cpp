//
// Created by Paolo on 29/01/2018.
//

#include "Transform.h"
#include "Utils.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;

Transform::Transform() {
    _pos = ZERO3;
    _rot = ZERO3;
    _scale = vec3(1.0f);
    _front = FRONT;
    _right = RIGHT;
    _up = UP;
    _updatedAxis = true;
}

glm::vec3 Transform::getPosition() const {
    return _pos;
}

glm::vec3 Transform::getRotation() const {
    return _rot;
}

glm::vec3 Transform::getScale() const {
    return _scale;
}

void Transform::setPosition(const glm::vec3& pos) {
    _pos = pos;
}

void Transform::setRotation(const glm::vec3& rot) {
    _rot = rot;
    _updatedAxis = false;
}

void Transform::setScale(const glm::vec3& scale) {
    _scale = scale;
}

void Transform::addPosition(const glm::vec3& pos) {
    _pos += pos;
}

void Transform::addRotation(const glm::vec3& rot) {
    _rot += rot;
    _updatedAxis = false;
}

glm::vec3 Transform::getFront() {
    if (_updatedAxis) {
        return _front;
    }
    _adjustAxis();
    return _front;
}

glm::vec3 Transform::getRight() {
    if (_updatedAxis) {
        return _right;
    }
    _adjustAxis();
    return _right;
}

glm::vec3 Transform::getUp() {
    if (_updatedAxis) {
        return _up;
    }
    _adjustAxis();
    return _up;
}

void Transform::_adjustAxis() {
    _front = glm::rotate(FRONT, _rot.y, UP);
    _right = glm::cross(UP, _front);
    _front = glm::rotate(_front, _rot.x, _right);
    _up = glm::cross(_front, _right);
    _up = glm::rotate(_up, _rot.z, _front);
    _right = glm::cross(_up, _front);
    _updatedAxis = true;
}

glm::mat4 Transform::getModelMatrix() const {
    auto model = glm::scale(IDENTITY_4, _scale);
    model = glm::rotate(model, _rot.y, UP);
    auto f = glm::rotate(FRONT, _rot.y, UP);
    auto r = glm::cross(UP, _front);
    model = glm::rotate(model, _rot.x, r);
    f = glm::rotate(f, _rot.x, r);
    model = glm::rotate(model, _rot.z, f);
    model = glm::translate(model, _pos);
    return model;
}