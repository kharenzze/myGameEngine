//
// Created by Paolo on 31/01/2018.
//

#ifndef MYGAMEENGINE_BUFFER_H
#define MYGAMEENGINE_BUFFER_H

#include <glad/glad.h>
class Buffer {
public:
    Buffer();
    GLuint getVAO() const;
    void setVerticesAndIndices(float* vertices, GLuint nVertices, float* indices, GLuint nIndices);
private:
    GLuint VAO, VBO, EBO;
};


#endif //MYGAMEENGINE_BUFFER_H
