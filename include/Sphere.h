//
// Created by Paolo on 21/01/2018.
//

#ifndef MYGAMEENGINE_SPHERE_H
#define MYGAMEENGINE_SPHERE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Geometry.h"

class Sphere : public Geometry {
public:
    Sphere();
    void uploadToGPU() override;
    glm::vec3 center;
    float radius;
    GLuint slices, stacks;
};


#endif //MYGAMEENGINE_SPHERE_H
