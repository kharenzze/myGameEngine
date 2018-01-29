//
// Created by Paolo on 29/01/2018.
//

#ifndef MYGAMEENGINE_TRANSFORM_H
#define MYGAMEENGINE_TRANSFORM_H

#include <glm/glm.hpp>

class Transform {
public:
    Transform();
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;
    void setPosition(const glm::vec3& pos);
    void setRotation(const glm::vec3& rot);
    void setScale(const glm::vec3& scale);
    void addPosition(const glm::vec3& pos);
    void addRotation(const glm::vec3& rot);
    glm::vec3 getFront();
    glm::vec3 getRight();
    glm::vec3 getUp();
    glm::mat4 getModelMatrix() const;
    /* TODO
     * void setFront(glm::vec3) const
     * void lookAt(glm::vec3) const
     * */
private:
    glm::vec3 _pos, _rot, _scale, _front, _right, _up;
    bool _updatedAxis;
    void _adjustAxis();
};


#endif //MYGAMEENGINE_TRANSFORM_H
