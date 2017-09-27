#version 150

in vec4 vPosition;
in vec4 vColor;
out vec4 passColor;

void main () {
    gl_Position = vPosition;
    passColor = vColor;
}