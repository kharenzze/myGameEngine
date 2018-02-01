//
// Created by Paolo on 31/01/2018.
//

#include "Geometry.h"
#include <iostream>

Geometry::Geometry() {
    _buffer = Buffer();
}

void Geometry::render() const {
    glBindVertexArray(_buffer.getVAO());
    glDrawElements(GL_TRIANGLES, _buffer.getNElements(), GL_UNSIGNED_INT, nullptr);
}

