//
// Created by Paolo on 21/12/2017.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

void render(GLuint VAO, GLuint shader) {
    clearScreen();
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

GLuint createVertexData(GLuint* VBO) {
    float vertices [] = {
        .5f, .5f, .0f,
        .5f, -.5f, .0f,
        -.5f, .5f, .0f,

        .5f, -.5f, .0f,
        -.5f, -.5f, .0f,
        -.5f, .5f, .0f
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}

bool checkShader(GLuint shader) {
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "Error Compiling Shader" << std::endl << infoLog << std::endl;

        return false;
    }
    return true;
}

bool checkProgram(GLuint program) {
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "Error Linking Program" << std::endl << infoLog << std::endl;

        return false;
    }
    return true;
}

GLuint createProgram() {
    const char * vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main(){\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";

    const char * fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main(){\n"
            "   FragColor = vec4(0.2f, .7f, .2f, 1.0f);\n"
            "}\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
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

    GLuint VBO;
    GLuint VAO = createVertexData(&VBO);
    GLuint shader = createProgram();


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

    glfwTerminate();
    return 0;
}

