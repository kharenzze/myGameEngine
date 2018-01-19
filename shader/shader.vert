#version 330core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCord;

out vec3 myColor;
out vec2 textCord;
out flat uint textNumber;

void main(){
    gl_Position = vec4(aPos, 1.0);
    myColor = aColor;
    textCord = aTextCord;
    if (aPos[0] > 0) {
        textNumber = 1;
    } else {
        textNumber = 2;
    }
}