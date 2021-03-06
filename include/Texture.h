//
// Created by Paolo on 01/02/2018.
//

#ifndef MYGAMEENGINE_TEXTURE_H
#define MYGAMEENGINE_TEXTURE_H

#include <glad/glad.h>

class Texture {
public:
    Texture(const char* path, const bool verticalFlip = true);
    ~Texture();
    GLuint getId() const;
    void bind() const;
private:
    GLuint _id;
};

#endif //MYGAMEENGINE_TEXTURE_H
