//
// Created by Paolo on 02/02/2018.
//

#include "Drawable.h"

Drawable::Drawable() {
    material = nullptr;
    geometry = nullptr;
}

Drawable::Drawable(Material *mat, Geometry *geo) {
    material = mat;
    geometry = geo;
}

void Drawable::draw(const Transform& self, const Camera& camera, const Transform* lightPos, const Light *light) {
    if (material && geometry) {
        material->use(self, camera, lightPos, light);
        geometry->render();
    }
}