//
// Created by Paolo on 02/02/2018.
//

#ifndef MYGAMEENGINE_LIGHT_H
#define MYGAMEENGINE_LIGHT_H

#include <glm/glm.hpp>

class Light {
public:
    Light();
    Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    glm::vec3 ambient, diffuse, specular;
};


#endif //MYGAMEENGINE_LIGHT_H
