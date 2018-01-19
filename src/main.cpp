//
// Created by Paolo on 21/12/2017.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

constexpr float maxFPS = 60.0f;
constexpr float maxFramePeriod = 1 / maxFPS;

constexpr double maxFPSDouble = 60.0;
constexpr double maxFramePeriodDouble = 1 / maxFPSDouble;

float interpolation = 0;
constexpr float interpolationRate = 0.01f;

void initConfiguration() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
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

void handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (interpolation < 1) {
            interpolation +=interpolationRate;
        }
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (interpolation > 0) {
            interpolation -=interpolationRate;
        }
    }
}

void clearScreen() {
    glClearColor(.2f, .2f, .7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render(const GLuint VAO, const Shader& shader, const GLuint text, const GLuint text2) {
    clearScreen();
    shader.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, text);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, text2);

    shader.set("texture_interpolation", interpolation);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

GLuint createVertexData(GLuint* VBO, GLuint* EBO) {
    float vertices [] = {
        .5f, .5f, .0f,      1, 1, 0,    1,1,
        .5f, -.5f, .0f,     1, 0, 0,    1,0,
        -.5f, -.5f, .0f,    0, 1, 0,    0,0,
        -.5f, .5f, .0f,     0, 0, 1,     0,1
    };

    GLuint indices [] = {
        0,3,1,
        1,3,2
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

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

    const GLuint text = createTexture("../texture/perro_texto.jpg");
    const GLuint text2 = createTexture("../texture/wood.jpg");

    initConfiguration();

    shader.use();
    shader.set("texture1", 0);
    shader.set("texture2", 1);

    double lastFrameTime = 0;

    while (!glfwWindowShouldClose(window)) { //Loop until user closes the window
        const auto currentTime = glfwGetTime();
        const auto dt = currentTime - lastFrameTime;
        if (dt > maxFramePeriodDouble) {
            lastFrameTime += dt;
            // Handle Input
            handleInput(window);
            //Render Here
            render(VAO, shader, text, text2);
            //Swap front and back buffers
            glfwSwapBuffers(window);
            // Poll for and process events
            glfwPollEvents();
        }
    }
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &EBO);

    glDeleteTextures(1, &text);
    glDeleteTextures(1, &text2);

    glfwTerminate();
    return 0;
}

