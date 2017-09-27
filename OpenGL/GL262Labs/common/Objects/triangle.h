#ifndef TRIANGLE_H_INCLUDED_
#define TRIANGLE_H_INCLUDED_

// For each face, vertices are added counter-clockwise (when the viewer is facing that face):
GLfloat vertices[] = {
    // front
    -1.0, -1.0,  1.0,
    1.0, -1.0,  1.0,
    1.0,  1.0,  1.0
};


GLfloat normals[] = {
    // front
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0
};

// The texture mapping is identical for all faces:
GLfloat UVs[] = {
    // front
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0
};

GLuint indices[] = {
    // front
    0,  1,  2
};


const int num_indices = sizeof( indices ) / sizeof( GLuint );
const int num_vertices = sizeof( vertices ) / sizeof( GLfloat ) / 3;
const int num_normals = sizeof( normals ) / sizeof( GLfloat ) / 3;
const int num_uvs = sizeof( UVs ) / sizeof( GLfloat ) / 2;


#endif //TRIANGLE_H_INCLUDED_
