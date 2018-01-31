#version 330core
out vec4 FragColor;
in vec4 gouraud;

void main() {
    FragColor = gouraud;
}