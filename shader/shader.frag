#version 330core
out vec4 FragColor;
in vec3 myColor;
in vec3 myPos;

void main(){
   FragColor = vec4(myPos, 1.0f);
}