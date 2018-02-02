//
// Created by Paolo on 01/02/2018.
//

#include "Material.h"
#include <iostream>

Material::Material(Shader* shader, const bool hasMaterialProps, const bool hasLightProps) {
    this->shader = shader;
    diffuse = nullptr;
    specular = nullptr;
    shininess = 32;
    _hasLightProps = hasLightProps;
    _hasMaterialProps = hasMaterialProps;
}

void Material::use(const Transform& self, const Camera& camera, const Transform* lightPos, const Light *light) const {
    shader->use();
    if (_hasMaterialProps) {
        if (diffuse) {
            glActiveTexture(GL_TEXTURE1);
            diffuse->bind();
            shader->set("material.diffuse", (int)diffuse->getId());
        }
        if (specular) {
            glActiveTexture(GL_TEXTURE2);
            specular->bind();
            shader->set("material.specular", (int)specular->getId());
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