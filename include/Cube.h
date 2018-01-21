//
// Created by Paolo on 21/01/2018.
//

#ifndef MYGAMEENGINE_CUBE_H
#define MYGAMEENGINE_CUBE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Cube {
public:
    static GLuint createVertexData(GLuint* VBO, GLuint* EBO, const glm::vec3 center, const float radius);
};


#endif //MYGAMEENGINE_CUBE_H
