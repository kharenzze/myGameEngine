#version 330core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextCord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMat;

uniform vec3 objColor;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform vec3 lightPos;

uniform vec3 viewPos;
uniform int shininess;
uniform float specularStrength;

out vec4 gouraud;

void main() {
    gl_Position =  projection * view * model * vec4(aPos, 1.0);

    //color
    vec3 fragPos = vec3(model * vec4(aPos, 1.0f));
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normalMat * aNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm ,lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    gouraud = vec4((ambient + diffuse + specular) * objColor, 1.0f);
}