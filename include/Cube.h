//
// Created by Paolo on 21/01/2018.
//

#ifndef MYGAMEENGINE_CUBE_H
#define MYGAMEENGINE_CUBE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Geometry.h"

class Cube : public Geometry {
public:
    Cube();
    void uploadToGPU() override;
    glm::vec3 center;
    float radius;
};


#endif //MYGAMEENGINE_CUBE_H
