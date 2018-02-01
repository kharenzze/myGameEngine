//
// Created by Paolo on 31/01/2018.
//

#ifndef MYGAMEENGINE_GEOMETRY_H
#define MYGAMEENGINE_GEOMETRY_H

#include "Buffer.h"


class Geometry {
public:
    Geometry();
    void virtual uploadToGPU() = 0;
    void render() const;
protected:
    Buffer _buffer;
};


#endif //MYGAMEENGINE_GEOMETRY_H
