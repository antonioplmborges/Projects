#ifndef SQUARE_H_INCLUDED_
#define SQUARE_H_INCLUDED_

GLfloat vertices[] = {
-1, -1, 1,      //    0    1
1, -1, 1,       //    1    2
1, 1, 1,        //    2    3
1, 1, 1,        //    3    4
-1, 1, 1,       //    4    5
-1, -1, 1       //    5    6
};
GLfloat normals[] = {
0, 0, 1,        //    0    1
0, 0, 1,        //    1    2
0, 0, 1,        //    2    3
0, 0, 1,        //    3    4
0, 0, 1,        //    4    5
0, 0, 1         //    5    6
};

GLfloat UVs[] = {
    // front
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0,
    0.0, 1.0
};

GLuint indices[] = {
0, 1, 2,
3, 4, 5,
};

const int num_indices = sizeof( indices ) / sizeof( GLuint );
const int num_vertices = sizeof( vertices ) / sizeof( GLfloat ) / 3;
const int num_normals = sizeof( normals ) / sizeof( GLfloat ) / 3;
const int num_uvs = sizeof( UVs ) / sizeof( GLfloat ) / 2;


#endif //SQUARE_H_INCLUDED_
