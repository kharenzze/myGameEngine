//
// Created by Pablo Ráez Sánchez on 11/1/18.
//

#ifndef MYGAMEENGINE_SHADER_H
#define MYGAMEENGINE_SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <cstdint>
#include <string>


class  Shader {
    enum class Type {
        Vertex = 0,
        Fragment = 1,
        Geometry = 2,
        Program = 3
    };

public:
    Shader(const char* vertexPath, const char* fragmentPath,
           const char* geometryPath = nullptr);
    ~Shader();

    void use() const;

    void set(const char* name, const bool value) const;
    void set(const char* name, const GLint value) const;
    void set(const char* name, const GLfloat value) const;
    void set(const char* name, const GLfloat value0, const GLfloat value1) const;
    void set(const char* name, const GLfloat value0, const GLfloat value1,
             const GLfloat value2) const;
    void set(const char* name, const GLfloat value0, const GLfloat value1,
             const GLfloat value2, const GLfloat value3) const;

    void set(const char* name, const glm::vec2& value) const;
    void set(const char* name, const glm::vec3& value) const;
    void set(const char* name, const glm::vec4& value) const;
    void set(const char* name, const glm::mat2& value) const;
    void set(const char* name, const glm::mat3& value) const;
    void set(const char* name, const glm::mat4& value) const;

private:
    Shader() {};

    static const char* typeToString (const Type type);
    void checkError(const GLuint shader, const Type type) const;
    void loadShader(const char* path, std::string* code);

    GLuint id_;
};
#endif //MYGAMEENGINE_SHADER_H
