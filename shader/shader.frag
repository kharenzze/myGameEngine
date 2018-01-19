#version 330core
out vec4 FragColor;
in vec3 myColor;
in vec2 textCord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    FragColor = mix(texture(texture1, textCord), texture(texture2, textCord), 0);
}