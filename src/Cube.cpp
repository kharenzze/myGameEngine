//
// Created by Paolo on 21/01/2018.
//

#include "Cube.h"

using glm::vec3;
using glm::vec2;

static constexpr GLuint _vertexMap[] = {
        1, 1, 1,      1,1,//front
        1, 0, 1,     1,0,
        0, 0, 1,    0,0,
        0, 1, 1,     0,1,

        1, 1, 0,      0,1,//back
        1, 0, 0,     0,0,
        0, 0, 0,    1,0,
        0, 1, 0,     1,1,

        1, 0, 1,     0,0,//Rigth
        1, 0, 0,     1,0,
        1, 1, 0,      1,1,
        1, 1, 1,      0,1,

        0, 0, 1,     1,0,//left
        0, 0, 0,     0,0,
        0, 1, 0,      0,1,
        0, 1, 1,      1,1,

        1, 1, 1,      1,0,//top
        1, 1, 0,     1,1,
        0, 1, 1,     0,0,
        0, 1, 0,    0,1,

        1, 0, 1,      1,1,//bottom
        1, 0, 0,     1,0,
        0, 0, 1,     0,1,
        0, 0, 0,    0,0,
};

static constexpr GLuint indices[] = {
        0,3,1,  1,3,2,
        7,4,6,  6,4,5,
        10,11,9,  9,11,8,
        15,14,12,  12,14,13,
        17,19,16,  16,19,18,
        20,22,21,  21,22,23,
};

constexpr GLuint numVertices = 24;

GLuint Cube::createVertexData(GLuint* VBO, GLuint* EBO, const vec3 center, const float radius) {
    const auto x = vec2(center.x - radius, center.x + radius);
    const auto y = vec2(center.y - radius, center.y + radius);
    const auto z = vec2(center.z - radius, center.z + radius);

    float vertices[numVertices * 5];

    for (int i = 0; i < numVertices; i++) {
        int offset = i*5;
        vertices[offset] = x[_vertexMap[offset]];
        offset++;
        vertices[offset] = y[_vertexMap[offset]];
        offset++;
        vertices[offset] = z[_vertexMap[offset]];
        offset++;
        vertices[offset] = _vertexMap[offset];
        offset++;
        vertices[offset] = _vertexMap[offset];
    }

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
}