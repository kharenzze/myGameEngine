#version 330core
out vec4 FragColor;
in vec3 myColor;

uniform float sin;

void main(){
   FragColor = vec4(sin * myColor, 1.0f);
}