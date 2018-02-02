//
// Created by Paolo on 01/02/2018.
//

#ifndef MYGAMEENGINE_MATERIAL_H
#define MYGAMEENGINE_MATERIAL_H

#include "glad/glad.h"
#include <glm/glm.hpp>
#include "shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"

class Material {
public:
    Material(Shader* shader, const bool hasMaterialProps, const bool hasLightProps);
    void use(const Transform& self, const Camera& camera, const Transform* lightPos = nullptr, const Light *light = nullptr) const;

    Texture *diffuseTexture, *specularTexture, *emisiveTexture;
    Shader* shader;
    glm::vec3 ambient, diffuse, specular;
    float shininess;
private:
    bool _hasMaterialProps, _hasLightProps;
};


#endif //MYGAMEENGINE_MATERIAL_H
