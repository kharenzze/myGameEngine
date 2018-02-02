//
// Created by Paolo on 02/02/2018.
//

#include "Light.h"
#include "Utils.h"

Light::Light() {
    ambient = ZERO3;
    diffuse = ZERO3;
    specular = ZERO3;
}

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}