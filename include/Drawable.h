//
// Created by Paolo on 02/02/2018.
//

#ifndef MYGAMEENGINE_DRAWABLE_H
#define MYGAMEENGINE_DRAWABLE_H


#include "Material.h"
#include "Geometry.h"

class Drawable {
public:
    Drawable();
    Drawable(Material *mat, Geometry *geo);
    void draw(const Transform& self, const Camera& camera, const Transform* lightPos = nullptr, const Light *light = nullptr);
    Material *material;
    Geometry *geometry;
};


#endif //MYGAMEENGINE_DRAWABLE_H
