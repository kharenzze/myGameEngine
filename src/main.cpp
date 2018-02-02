//
// Created by Paolo on 21/12/2017.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "Utils.h"
#include "Camera.h"
#include "Mouse.h"
#include "Cube.h"
#include "Sphere.h"
#include "GameObject.h"
#include "Texture.h"
#include "Light.h"
#include "Drawable.h"

#include <iostream>

constexpr float maxFPS = 60.0f;
constexpr float maxFramePeriod = 1 / maxFPS;

constexpr double maxFPSDouble = 60.0;
constexpr double maxFramePeriodDouble = 1 / maxFPSDouble;

constexpr GLuint K_SCREEN_WIDTH = 800;
constexpr GLuint K_SCREEN_HEIGHT = 800;

constexpr float K_SCREEN_RATIO = K_SCREEN_WIDTH / K_SCREEN_HEIGHT;

Camera camera(2.0f, glm::vec3(-1,2,3), 45.0f);
Mouse mouse;
bool firstMouse = true;

GameObject cubeObject = GameObject();
GameObject light = GameObject();

void initConfiguration() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
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

void render() {
    clearScreen();

    light.drawable->draw(light.transform, camera, nullptr);

    cubeObject.transform.addRotation(glm::vec3(0.0f, 0.01f, 0.0f));
    cubeObject.drawable->draw(cubeObject.transform, camera, &light.transform, light.light);
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

    auto cube = Cube();
    cube.uploadToGPU();

    auto sphere = Sphere();
    sphere.uploadToGPU();

    Shader shader("../shader/shader.vert", "../shader/shader.frag");
    Shader shader_light("../shader/shader_light.vert", "../shader/shader_light.frag");
    Shader shader_flat("../shader/flat.vert", "../shader/flat.frag");

    auto textDiffuse = Texture("../texture/stone_diffuse.jpg");
    auto textSpec = Texture("../texture/stone_specular.jpg");

    Material matLight(&shader_light, false, false);
    Material matCube(&shader, true, true);
    matCube.diffuseTexture = &textDiffuse;
    matCube.specularTexture = &textSpec;

    auto lightDrawable = Drawable(&matLight, &sphere);
    auto cubeDrawable = Drawable(&matCube, &cube);

    light.drawable = &lightDrawable;
    light.transform.setPosition(glm::vec3(1.2f, 1.0f, 1.0f));
    light.transform.setScale(glm::vec3(0.3f));
    auto l = Light(glm::vec3(0.1f, 0.1f, 0.1f),
                   glm::vec3(0.7f, 0.0f, 0.0f),
                   glm::vec3(0.0f, 0.0f, 1.0f));
    light.light = &l;

    cubeObject.drawable = &cubeDrawable;

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
            render();
            //Swap front and back buffers
            glfwSwapBuffers(window);
            // Poll for and process events
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}

