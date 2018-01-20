#version 330core
out vec4 FragColor;

in vec2 textCord;

uniform sampler2D texture1;

void main(){
    FragColor = texture(texture1, textCord);
}