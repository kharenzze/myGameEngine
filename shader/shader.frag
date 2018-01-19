#version 330core
out vec4 FragColor;
in vec3 myColor;
in vec2 textCord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    vec2 localCord = vec2(textCord[0], 1 - textCord[1]);
    FragColor = texture(texture1, localCord);
}