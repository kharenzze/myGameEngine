//
// Created by Paolo on 29/01/2018.
//

#ifndef MYGAMEENGINE_GAMEOBJECT_H
#define MYGAMEENGINE_GAMEOBJECT_H

#include "Transform.h"
#include "Drawable.h"
#include "Light.h"
#include "Collider.h"

class GameObject {
public:
    GameObject();
    Transform transform;
    Drawable *drawable;
    Light *light;
    Collider *collider;
};


#endif //MYGAMEENGINE_GAMEOBJECT_H
