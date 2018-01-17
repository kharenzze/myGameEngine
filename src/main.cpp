//
// Created by Paolo on 21/12/2017.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

#include <iostream>

void onChangeFramebufferSize(GLFWwindow* window, const int32_t width, const int32_t height) {
    glViewport(0, 0, width, height);
}

void handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void clearScreen() {
    glClearColor(.2f, .2f, .7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render(GLuint VAO, Shader& shader) {
    clearScreen();
    shader.use();
    glBindVertexArray(VAO);
    const auto t = glfwGetTime();
    const float sin = .5f * glm::sin(t) + .5f;
    shader.set("sin", sin);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

GLuint createVertexData(GLuint* VBO, GLuint* EBO) {
    float vertices [] = {
        -.5f, -.5f, .0f,    1, 0, 0,
        0, .5f, .0f,        0, 1, 0,
        .5f, -.5f, .0f,     0, 0, 1
    };

    GLuint indices [] = {
        0,2,1
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return VAO;
}

int main (int argc, char *argv[]) {

    if (!glfwInit()) {       //Initialize the library
        std::cout << "Failed To Initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //Core Profile

    GLFWwindow* window;    //Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(800, 600, "New Window", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed To Create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);  //Make the window's context current

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {  //Init GLAD
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, &onChangeFramebufferSize);

    GLuint VBO, EBO;
    GLuint VAO = createVertexData(&VBO, &EBO);

    Shader shader("../shader/shader.vert", "../shader/shader.frag");

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    while (!glfwWindowShouldClose(window)) { //Loop until user closes the window
        // Handle Input
        handleInput(window);
        //Render Here
        render(VAO, shader);
        //Swap front and back buffers
        glfwSwapBuffers(window);
        // Poll for and process events
        glfwPollEvents();
    }
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &EBO);

    glfwTerminate();
    return 0;
}

