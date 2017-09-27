#ifndef MODEL
#define MODEL
#include "Shader.h"

class Model {
public:
    Model(Shader* shader);
    ~Model();
    void set_geometry(GLfloat vertices[], int size);
    void set_normals(GLfloat* normals, int size);
    void set_vertex_colors(GLfloat* colors, int size);
    void set_texture_coordinates(GLfloat* uvs, int size);
    void upload_2_server();
    void render();
private:
    Shader* shader;        // The shader object for this model
    GLfloat* vertices;    // x, y, z
    GLfloat* normals;    // Vertex normals
    GLfloat* uvs;        // Texture coordinates
    GLfloat* colors;    // Colors for each vertex
    GLuint total_vertices, total_normals, total_UVs, total_colors;
    GLuint vao;            // Vertex Array Object
    GLuint vbo;            // Vertex Buffer Object

    GLuint vPosition;    // A handle for the variable "vPosition" in the shader
    GLuint vNormal;        // A handle for the variable "vNormal" in the shader
    GLuint vTexCoord;    // A handle for the variable "vTexCoord" in the shader
    GLuint vColor;        // A handle for the variable "vColor" in the shader

};
#endif