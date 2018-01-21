//
// Created by Paolo on 21/01/2018.
//

#ifndef MYGAMEENGINE_MOUSE_H
#define MYGAMEENGINE_MOUSE_H

#include <glm/glm.hpp>

class Mouse {
public:
    Mouse();
    glm::vec2 getPos() const;
    glm::vec2 getDelta() const;
    void setPos(glm::vec2 npos);
    float sensitivity;
private:
    glm::vec2 _pos;
    glm::vec2 _delta;
};


#endif //MYGAMEENGINE_MOUSE_H
