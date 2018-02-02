//
// Created by Paolo on 01/02/2018.
//

#include "Material.h"
#include <iostream>
#include "Utils.h"

Material::Material(Shader* shader, const bool hasMaterialProps, const bool hasLightProps) {
    this->shader = shader;
    diffuseTexture = nullptr;
    specularTexture = nullptr;
    shininess = 32;
    _hasLightProps = hasLightProps;
    _hasMaterialProps = hasMaterialProps;
    ambient = ZERO3;
    diffuse = ZERO3;
    specular = ZERO3;
}

void Material::use(const Transform& self, const Camera& camera, const Transform* lightPos, const Light *light) const {
    shader->use();
    if (_hasMaterialProps) {
        if (diffuseTexture) {
            glActiveTexture(GL_TEXTURE1);
            diffuseTexture->bind();
            shader->set("material.diffuse", (int)diffuseTexture->getId());
        } else {
            shader->set("material.diffuse", diffuse);
            shader->set("material.ambient", ambient);
        }
        if (specularTexture) {
            glActiveTexture(GL_TEXTURE2);
            specularTexture->bind();
            shader->set("material.specular", (int)specularTexture->getId());
        } else {
            shader->set("material.specular", specular);
        }
        shader->set("material.shininess", shininess);
    }
    if (_hasLightProps) {
        if (light) {
            shader->set("light.ambient", light->ambient);
            shader->set("light.diffuse", light->diffuse);
            shader->set("light.specular", light->specular);
            shader->set("light.position", lightPos->getPosition());
            const auto normalMat = glm::transpose(glm::inverse(glm::mat3(self.getModelMatrix())));
            shader->set("normalMat", normalMat);
        } else {
            std::cout << "Error: bad light on material" << std::endl;
        }
    }
    shader->set("viewPos", camera.pos);
    shader->set("projection", camera.getPerspectiveMatrix());
    shader->set("view", camera.getViewMatrix());
    const auto model = self.getModelMatrix();
    shader->set("model", model);

}