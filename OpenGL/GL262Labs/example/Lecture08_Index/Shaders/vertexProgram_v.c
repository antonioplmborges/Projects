#version 130

in vec4 s_vPosition;
in vec4 s_vColor;
out vec4 color;

void main () {
    color = s_vColor;
    // To be visible, s_vPosition should be between -1.0 and +1.0
    gl_Position = s_vPosition;
}
