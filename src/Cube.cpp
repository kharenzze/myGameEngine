//
// Created by Paolo on 21/01/2018.
//

#include "Cube.h"

using glm::vec3;
using glm::vec2;

Cube::Cube() {
    center = vec3(0);
    radius = 0.5f;
}

static constexpr int _vertexMap[] = {
        1, 1, 1,      1,1,      0,0,1,//front
        1, 0, 1,     1,0,       0,0,1,
        0, 0, 1,    0,0,        0,0,1,
        0, 1, 1,     0,1,       0,0,1,

        1, 1, 0,      0,1,      0,0,-1,//back
        1, 0, 0,     0,0,       0,0,-1,
        0, 0, 0,    1,0,        0,0,-1,
        0, 1, 0,     1,1,       0,0,-1,

        1, 0, 1,     0,0,       1,0,0,//Rigth
        1, 0, 0,     1,0,       1,0,0,
        1, 1, 0,      1,1,      1,0,0,
        1, 1, 1,      0,1,      1,0,0,

        0, 0, 1,     1,0,       -1,0,0,//left
        0, 0, 0,     0,0,       -1,0,0,
        0, 1, 0,      0,1,      -1,0,0,
        0, 1, 1,      1,1,      -1,0,0,

        1, 1, 1,      1,0,      0,1,0,//top
        1, 1, 0,     1,1,       0,1,0,
        0, 1, 1,     0,0,       0,1,0,
        0, 1, 0,    0,1,        0,1,0,

        1, 0, 1,      1,1,      0,-1,0,//bottom
        1, 0, 0,     1,0,       0,-1,0,
        0, 0, 1,     0,1,       0,-1,0,
        0, 0, 0,    0,0,        0,-1,0,
};

static constexpr GLuint indices[] = {
        0,3,1,  1,3,2,
        7,4,6,  6,4,5,
        10,11,9,  9,11,8,
        15,14,12,  12,14,13,
        17,19,16,  16,19,18,
        20,22,21,  21,22,23,
};

static constexpr GLuint nIndices = 36;

void Cube::uploadToGPU() {
    const auto x = vec2(center.x - radius, center.x + radius);
    const auto y = vec2(center.y - radius, center.y + radius);
    const auto z = vec2(center.z - radius, center.z + radius);

    constexpr GLuint numVertices = 24;
    const auto _dataPerRow = _buffer.getDataPerRow();
    const auto nVerticesData = numVertices * _dataPerRow;
    float vertices[nVerticesData];

    for (int i = 0; i < numVertices; i++) {
        int offset = i*_dataPerRow;
        vertices[offset] = x[_vertexMap[offset]];
        offset++;
        vertices[offset] = y[_vertexMap[offset]];
        offset++;
        vertices[offset] = z[_vertexMap[offset]];
        offset++;
        vertices[offset] = _vertexMap[offset];
        offset++;
        vertices[offset] = _vertexMap[offset];
        offset++;
        vertices[offset] = _vertexMap[offset];
        offset++;
        vertices[offset] = _vertexMap[offset];
        offset++;
        vertices[offset] = _vertexMap[offset];

    }
    _buffer.setVerticesAndIndices(vertices, nVerticesData, indices, nIndices);
}