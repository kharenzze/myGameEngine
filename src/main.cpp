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

GameObject cubes[5];
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
    for (int i = 5; i--;) {
        cubes[i].drawable->draw(cubes[i].transform, camera, &light.transform, light.light);
    }
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

    Material matLight(&shader_light, false, false);
    auto lightDrawable = Drawable(&matLight, &sphere);

    Material emerald(&shader_flat, true, true);
    emerald.ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
    emerald.diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);
    emerald.specular = glm::vec3(0.633f, 0.727811f, 0.633f);
    emerald.shininess = 0.6f * 128;
    auto emeraldDrawable = Drawable(&emerald, &cube);

    Material bronze(&shader_flat, true, true);
    bronze.ambient = glm::vec3(0.2125f, 0.1275f, 0.054f);
    bronze.diffuse = glm::vec3(0.714f, 0.4284f, 0.18144f);
    bronze.specular = glm::vec3(0.393548f, 0.271906f, 0.166721f);
    bronze.shininess = 0.2f * 128;
    auto bronzeDrawable = Drawable(&bronze, &cube);

    Material silver(&shader_flat, true, true);
    silver.ambient = glm::vec3(0.19225f, 0.19225f, 0.19225f);
    silver.diffuse = glm::vec3(0.50754f, 0.50754f, 0.50754f);
    silver.specular = glm::vec3(0.508273f, 0.508273f, 0.508273f);
    silver.shininess = 0.4f * 128;
    auto silverDrawable = Drawable(&silver, &cube);

    Material greenPlastic(&shader_flat, true, true);
    greenPlastic.ambient = glm::vec3(0);
    greenPlastic.diffuse = glm::vec3(0.1f, 0.35f, 0.1f);
    greenPlastic.specular = glm::vec3(0.45f, 0.55f, 0.45f);
    greenPlastic.shininess = 0.25f * 128;
    auto greenPlasticDrawable = Drawable(&greenPlastic, &cube);

    Material yellowRubber(&shader_flat, true, true);
    yellowRubber.ambient = glm::vec3(0.05f, 0.05f, 0);
    yellowRubber.diffuse = glm::vec3(0.5f, 0.5f, 0.4f);
    yellowRubber.specular = glm::vec3(0.7f, 0.7f, 0.04f);
    yellowRubber.shininess = 0.078125f * 128;
    auto yellowRubberDrawable = Drawable(&yellowRubber, &cube);


    light.drawable = &lightDrawable;
    light.transform.setPosition(glm::vec3(0, 1.0f, 1.0f));
    light.transform.setScale(glm::vec3(0.3f));
    auto l = Light(glm::vec3(0.2f, 0.15f, 0.1f),
                   glm::vec3(0.7f, 0.7f, 0.7f),
                   glm::vec3(1.0f, 1.0f, 1.0f));
    light.light = &l;

    cubes[0] = GameObject();
    cubes[0].drawable = &emeraldDrawable;
    cubes[0].transform.setPosition(glm::vec3(-2, 0, -2));

    cubes[1] = GameObject();
    cubes[1].drawable = &bronzeDrawable;
    cubes[1].transform.setPosition(glm::vec3(-2, 0, 2));

    cubes[2] = GameObject();
    cubes[2].drawable = &silverDrawable;
    cubes[2].transform.setPosition(glm::vec3(2, 0, -2));

    cubes[3] = GameObject();
    cubes[3].drawable = &greenPlasticDrawable;
    cubes[3].transform.setPosition(glm::vec3(0, 0, 0));

    cubes[4] = GameObject();
    cubes[4].drawable = &yellowRubberDrawable;
    cubes[4].transform.setPosition(glm::vec3(2, 0, 2));

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

