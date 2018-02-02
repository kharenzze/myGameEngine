#version 330core
out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 textCord;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;
uniform vec3 viewPos;

void main(){
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, textCord));

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm ,lightDir), 0.0f);
    vec3 diffuse = diff * vec3(texture(material.diffuse, textCord)) * light.diffuse;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = (vec3(1) - vec3(texture(material.specular, textCord))) * spec * light.specular;

    vec3 phong = ambient + diffuse + specular;
    FragColor = vec4(phong, 1.0);
}