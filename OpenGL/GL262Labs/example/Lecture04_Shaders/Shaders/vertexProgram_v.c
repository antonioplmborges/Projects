#version 130

in vec4 s_vPosition;

void main () {
    // To be visible, s_vPosition should be between -1.0 and +1.0
    gl_Position = s_vPosition;
}
