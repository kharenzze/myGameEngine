#version 330core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMat;

out vec3 normal;
out vec3 fragPos;

void main() {
    normal = normalMat * aNormal;
    normal = vec3(view * vec4(normal, 0.0f));
    fragPos = vec3(view * model * vec4(aPos, 1.0f));
    gl_Position =  projection * view * model * vec4(aPos, 1.0);
}