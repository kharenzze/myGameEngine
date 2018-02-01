//
// Created by Paolo on 31/01/2018.
//

#include "Buffer.h"

static constexpr GLuint _dataPerRow = 8;

Buffer::Buffer() {
    VAO = 0;
    VBO = 0;
    EBO = 0;
    nElements = 0;
}

GLuint Buffer::getVAO() const {
    return VAO;
}

GLuint Buffer::getDataPerRow() const {
    return _dataPerRow;
}

GLuint Buffer::getNElements() const {
    return nElements;
}

void Buffer::setVerticesAndIndices(const float* vertices, const GLuint nVerticesData, const GLuint* indices, const GLuint nIndices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, nVerticesData * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _dataPerRow * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, _dataPerRow * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, _dataPerRow * sizeof(float), (void *) (5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    nElements = nIndices;
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}

