//
// Created by Paolo on 21/01/2018.
//

#include "Mouse.h"

using glm::vec2;

Mouse::Mouse() {
    _pos = vec2(0);
    sensitivity = 0.1f;
}

vec2 Mouse::getPos() const {
    return _pos;
}

void Mouse::setPos(vec2 pos) {
    _delta = pos - _pos;
    _pos = pos;
}

vec2 Mouse::getDelta() const {
    return _delta;
}