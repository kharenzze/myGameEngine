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

const auto identity4 = glm::mat4(1.0f);

#endif //MYGAMEENGINE_UTILS_H
