//
// Created by Paolo on 20/01/2018.
//

#ifndef MYGAMEENGINE_UTILS_H
#define MYGAMEENGINE_UTILS_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

float inline _glfwGetTimeFloat() {
    return glfwGetTime();
}

const glm::mat4 IDENTITY_4 = glm::mat4(1.0f);

const glm::vec3 FRONT = glm::vec3(0, 0, 1);
const glm::vec3 UP = glm::vec3(0, 1, 0);
const glm::vec3 RIGHT = glm::vec3(1, 0, 0);

#endif //MYGAMEENGINE_UTILS_H
