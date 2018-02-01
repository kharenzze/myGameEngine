//
// Created by Paolo on 31/01/2018.
//

#ifndef MYGAMEENGINE_BUFFER_H
#define MYGAMEENGINE_BUFFER_H

#include <glad/glad.h>
class Buffer {
public:
    Buffer();
    ~Buffer();
    GLuint getVAO() const;
    void setVerticesAndIndices(const float* vertices,const GLuint nVertices,const GLuint* indices,const GLuint nIndices);
    GLuint getDataPerRow() const;
    GLuint getNElements() const;
private:
    GLuint VAO, VBO, EBO, nElements;
};


#endif //MYGAMEENGINE_BUFFER_H
