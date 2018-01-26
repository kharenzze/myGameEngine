//
// Created by Paolo on 21/12/2017.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "Utils.h"
#include "Camera.h"
#include "Mouse.h"
#include "Cube.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

constexpr float maxFPS = 60.0f;
constexpr float maxFramePeriod = 1 / maxFPS;

constexpr double maxFPSDouble = 60.0;
constexpr double maxFramePeriodDouble = 1 / maxFPSDouble;

constexpr GLuint K_SCREEN_WIDTH = 800;
constexpr GLuint K_SCREEN_HEIGHT = 800;

Camera camera(2.0f, glm::vec3(-1,2,3), 45.0f);
Mouse mouse;
bool firstMouse = true;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


void initConfiguration() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}

GLuint createTexture(const char* path, const int verticalFlip = 0) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nChannels;
    stbi_set_flip_vertically_on_load(!verticalFlip);
    unsigned char* data = stbi_load(path, &width, &height, &nChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    return texture;
}

void onChangeFramebufferSize(GLFWwindow* window, const int32_t width, const int32_t height) {
    glViewport(0, 0, width, height);
}

void handleInput(GLFWwindow* window,const float dt) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return;
    }

    auto cameraMovement = glm::vec3(0);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraMovement += camera.getFront();
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraMovement -= camera.getFront();
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraMovement += camera.getRight();
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraMovement -= camera.getRight();
    }

    camera.pos -= cameraMovement * camera.speed * dt;
}

void onScroll(GLFWwindow* window, double xoffset, double yOffset) {
    camera.moveFov(-yOffset);
}

void onMouse(GLFWwindow* window, double xPos, double yPos) {
    mouse.setPos(glm::vec2(xPos, yPos));
    if (firstMouse) {
        firstMouse = false;
        return;
    }
    auto dMouse = mouse.getDelta();
    auto r = glm::vec3(dMouse.y, dMouse.x, 0) * mouse.sensitivity;
    camera.addRotation(r);
}

void clearScreen() {
    glClearColor(.0f, .0f, .0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render(const GLuint VAO, const Shader& shader, const Shader& shader_light) {
    clearScreen();

    const auto projection = glm::perspective(glm::radians(camera.getFov()), (float)K_SCREEN_WIDTH/(float)K_SCREEN_HEIGHT, 0.1f, 100.0f);
    const auto view = camera.getViewMatrix();
    shader_light.use();

    shader_light.set("projection", projection);
    shader_light.set("view", view);

    auto model = glm::translate(IDENTITY_4, lightPos);
    model = glm::scale(model, glm::vec3(0.3f));
    shader_light.set("model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    shader.use();

    shader.set("projection", projection);
    shader.set("view", view);
    shader.set("model", IDENTITY_4);
    shader.set("light.ambient", glm::vec3(0.2f, 0.15f, 0.1f));
    shader.set("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
    shader.set("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader.set("light.shininess", 32.0f);
    shader.set("light.position", lightPos);
    const glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    shader.set("normalMat", normalMat);
    shader.set("viewPos", camera.pos);

    shader.set("material.ambient", glm::vec3(1.0f, 0.5f, 0.3f));
    shader.set("material.diffuse", glm::vec3(1.0f, 0.5f, 0.3f));
    shader.set("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader.set("material.shininess", 32.0f);


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
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
    window = glfwCreateWindow(K_SCREEN_WIDTH, K_SCREEN_HEIGHT, "New Window", nullptr, nullptr);
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

    glfwSetCursorPosCallback(window, onMouse);
    glfwSetScrollCallback(window, onScroll);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLuint VBO, EBO;
    GLuint VAO = Cube::createVertexData(&VBO, &EBO, ZERO3, 0.5f);


    Shader shader("../shader/shader.vert", "../shader/shader.frag");
    Shader shader_light("../shader/shader_light.vert", "../shader/shader_light.frag");

    initConfiguration();

    double lastFrameTime = 0;

    while (!glfwWindowShouldClose(window)) { //Loop until user closes the window
        const auto currentTime = glfwGetTime();
        const auto dt = currentTime - lastFrameTime;
        if (dt > maxFramePeriodDouble) {
            lastFrameTime += dt;
            // Handle Input
            handleInput(window, dt);
            //Render Here
            render(VAO, shader, shader_light);
            //Swap front and back buffers
            glfwSwapBuffers(window);
            // Poll for and process events
            glfwPollEvents();
        }
    }
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &EBO);

    glfwTerminate();
    return 0;
}

