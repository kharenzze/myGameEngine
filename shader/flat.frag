#version 330core
out vec4 FragColor;

uniform vec3 objColor;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform vec3 lightPos;

in vec3 norm;
in vec3 fragPos;

void main() {
//color
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm ,lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    FragColor = vec4((ambient + diffuse) * objColor, 1.0f);
}