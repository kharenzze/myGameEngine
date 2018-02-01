//
// Created by Paolo on 20/01/2018.
//

#ifndef MYGAMEENGINE_CAMERA_H
#define MYGAMEENGINE_CAMERA_H

#include <glm/glm.hpp>

#include "Utils.h"

const glm::vec3 cameraUp = UP;


class Camera {
public:
    Camera();
    Camera(const float speed, const glm::vec3 &pos, const float fov = 45.0f, const float screenRatio = 1.0f);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getPerspectiveMatrix() const;
    float getFov() const;
    void setFov(float fov);
    void moveFov(float offset);
    void setRotation(const glm::vec3 &rotation);
    void addRotation(const glm::vec3 &rotation);
    void setScreenRatio(const float ratio);
    glm::vec3 getFront() const;
    glm::vec3 getRight() const;
    glm::vec3 getFPSFront() const;
    glm::vec3 getFPSRight() const;

    glm::vec3 pos;
    float speed;

private:
    void _adjustRotation();
    void _calculateFront();

    float fov, _screenRatio;
    glm::vec3 _rotation;
    glm::vec3 _front;
};


#endif //MYGAMEENGINE_CAMERA_H
