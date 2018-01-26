#version 330core
out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 objColor;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform vec3 lightPos;


void main(){
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightColor - fragPos);
    float diff = max(dot(norm ,lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 phong = (ambientStrength + diffuse) * objColor;
    FragColor = vec4(phong, 1.0);
}