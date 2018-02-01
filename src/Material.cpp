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

void Material::use(const Transform& self, const Camera& camera, const Transform* light) const {
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
            shader->set("light.ambient", glm::vec3(0.2f, 0.15f, 0.1f));
            shader->set("light.diffuse", glm::vec3(0.7f, 0.7f, 0.7f));
            shader->set("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
            shader->set("light.position", light->getPosition());
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