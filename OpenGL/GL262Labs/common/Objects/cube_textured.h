#ifndef CUBE_TEXTURED_H_INCLUDED_
#define CUBE_TEXTURED_H_INCLUDED_

// For each face, vertices are added counter-clockwise (when the viewer is facing that face):
GLfloat vertices[] = {  // .h   .obj
    // front
    -1.0, -1.0,  1.0,   //  0   1
    1.0, -1.0,  1.0,    //  1   2
    1.0,  1.0,  1.0,    //  2   3
    -1.0,  1.0,  1.0,   //  3   4
    // top
    -1.0,  1.0,  1.0,   //  4   5
    1.0,  1.0,  1.0,    //  5   6
    1.0,  1.0, -1.0,    //  6   7
    -1.0,  1.0, -1.0,   //  7   8
    // back
    1.0, -1.0, -1.0,    //  8   9
    -1.0, -1.0, -1.0,   //  9  10
    -1.0,  1.0, -1.0,   // 10  11
    1.0,  1.0, -1.0,    // 11  12
    // bottom
    -1.0, -1.0, -1.0,   // 12  13
    1.0, -1.0, -1.0,    // 13  14
    1.0, -1.0,  1.0,    // 14  15
    -1.0, -1.0,  1.0,   // 15  16
    // left
    -1.0, -1.0, -1.0,   // 16  17
    -1.0, -1.0,  1.0,   // 17  18
    -1.0,  1.0,  1.0,   // 18  19
    -1.0,  1.0, -1.0,   // 19  20
    // right
    1.0, -1.0,  1.0,    // 20  21
    1.0, -1.0, -1.0,    // 21  22
    1.0,  1.0, -1.0,    // 22  23
    1.0,  1.0,  1.0     // 23  24
};


GLfloat normals[] = {
    // front
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    // top
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    // back
    0.0, 0.0, -1.0,
    0.0, 0.0, -1.0,
    0.0, 0.0, -1.0,
    0.0, 0.0, -1.0,
    // bottom
    0.0, -1.0, 0.0,
    0.0, -1.0, 0.0,
    0.0, -1.0, 0.0,
    0.0, -1.0, 0.0,
    // left
    -1.0, 0.0, 0.0,
    -1.0, 0.0, 0.0,
    -1.0, 0.0, 0.0,
    -1.0, 0.0, 0.0,
    // right
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0
};

// The texture mapping is identical for all faces:
GLfloat UVs[] = {
    // front
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0,
    // top
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0,
    // back
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0,
    // bottom
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0,
    // left
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0,
    // right
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0
};

GLuint indices[] = {
    // front
    0,  1,  2,
    2,  3,  0,
    // top
    4,  5,  6,
    6,  7,  4,
    // back
    8,  9, 10,
    10, 11,  8,
    // bottom
    12, 13, 14,
    14, 15, 12,
    // left
    16, 17, 18,
    18, 19, 16,
    // right
    20, 21, 22,
    22, 23, 20
};


const int num_indices = sizeof( indices ) / sizeof( GLuint );
const int num_vertices = sizeof( vertices ) / sizeof( GLfloat ) / 3;
const int num_normals = sizeof( normals ) / sizeof( GLfloat ) / 3;
const int num_uvs = sizeof( UVs ) / sizeof( GLfloat ) / 2;


#endif //CUBE_TEXTURED_H_INCLUDED_
