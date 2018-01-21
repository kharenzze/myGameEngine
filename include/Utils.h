//
// Created by Paolo on 20/01/2018.
//

#ifndef MYGAMEENGINE_UTILS_H
#define MYGAMEENGINE_UTILS_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
const glm::mat4 IDENTITY_4 = glm::mat4(1.0f);

const glm::vec3 FRONT = glm::vec3(0, 0, 1);
const glm::vec3 UP = glm::vec3(0, 1, 0);
const glm::vec3 RIGHT = glm::vec3(1, 0, 0);

const glm::vec3 ZERO3 = glm::vec3(0);

float inline _glfwGetTimeFloat() {
    return glfwGetTime();
}

void inline printVector3(const char* name, const glm::vec3 &v) {
    printf("%s: x: %f, y: %f, z: %f\n", name, &v.x, &v.y, &v.z);
}

#endif //MYGAMEENGINE_UTILS_H
