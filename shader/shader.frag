#version 330core
out vec4 FragColor;
in vec3 myColor;
in vec2 textCord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(){
    vec2 localCord = 2 * textCord;
    FragColor = mix(texture(texture1, localCord), texture(texture2, localCord), 0);
}