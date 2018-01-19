#version 330core
out vec4 FragColor;
in vec4 gl_FragCoord;

in vec3 myColor;
in vec2 textCord;
in flat uint textNumber;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float zoom;

void main(){
    vec2 localTextCord = textCord * zoom;
    if (textNumber == 1) {
        FragColor = texture(texture1, localTextCord);
    } else {
        FragColor = texture(texture2, localTextCord);
    }
}