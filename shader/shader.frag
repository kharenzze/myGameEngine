#version 330core
out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;


void main(){
    vec3 ambient = material.ambient * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightColor - fragPos);
    float diff = max(dot(norm ,lightDir), 0.0f);
    vec3 diffuse = diff * material.diffuse * lightColor;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = material.specular * spec * lightColor;

    vec3 phong = ambient + diffuse + specular;
    FragColor = vec4(phong, 1.0);
}