#version 330core
out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 objColor;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform vec3 lightPos;

uniform mat4 view;
vec3 viewPos = vec3(0,0,0);
uniform int shininess;
uniform float specularStrength;


void main(){
    vec3 lightPosView = vec3(view * vec4(lightPos, 1.0f));
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPosView - fragPos);
    float diff = max(dot(norm ,lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 phong = (ambientStrength + diffuse + specular) * objColor;
    FragColor = vec4(phong, 1.0);
}