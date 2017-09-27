//#define UNILOG_TRACING_ON "trace.log"
//#include "../../Unilog301/source/Server/MonoClient.h"

#include "Model.h"

// From http://www.opengl.org/registry/specs/EXT/pixel_buffer_object.txt 
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

Model::Model(Shader* shader) {
    this->shader = shader;
    glGenVertexArrays(1, &vao);                            // Generate a VAO
    glGenBuffers(1, &vbo);                                // Generate a buffer object
    vertices = normals = uvs = colors = NULL;            // Assume no vertex information
    total_vertices = total_normals = total_UVs = total_colors = 0;    // Set all sizes to 0
}
Model::~Model() {
    glDisableVertexAttribArray(vPosition);
    glDisableVertexAttribArray(vNormal);
    glDisableVertexAttribArray(vTexCoord);
    glDisableVertexAttribArray(vColor);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    delete (shader);
    delete (vertices);
    delete (normals);
    delete (uvs);
    delete (colors);
}

//Begin data upload functions
void Model::set_geometry(GLfloat* vertices, int size){
    printf ("Copying %d vertices\n", size/sizeof(GLfloat)/3);
    this->vertices = vertices;
    this->total_vertices = size/sizeof(GLfloat)/3;
    vPosition = glGetAttribLocation(shader->program_ID, "vPosition");
    printf ("vPosition ID is: %d\n", vPosition);
}
void Model::set_normals(GLfloat* normals, int size){
    printf ("Copying %d normals....\n", size/sizeof(GLfloat)/3);
    this->normals = normals;
    this->total_normals = size/sizeof(GLfloat)/3;
    vNormal = glGetAttribLocation(shader->program_ID, "vNormal");
    printf ("vNormal ID is: %d\n", vNormal);
}
void Model::set_vertex_colors(GLfloat* colors, int size){
    printf ("Copying %d colors...\n", size/sizeof(GLfloat)/4);
    this->colors = colors;
    this->total_colors = size/sizeof(GLfloat)/4;
    vColor = glGetAttribLocation(shader->program_ID, "vColor");
    printf ("vColor ID is: %d\n", vColor);
}
void Model::set_texture_coordinates(GLfloat* uvs, int size){
    printf ("Copying uvs...\n");
    this->uvs = uvs;
    this->total_UVs = size/sizeof(GLfloat)/2;
    vTexCoord = glGetAttribLocation(shader->program_ID, "vTexCoord");
    printf ("vTexCoord ID is: %d\n", vTexCoord);
}
//End data upload functions

// Pre-condition: You must have called at least one of the functions above
// This function loads all of the data onto the GPU.
void Model::upload_2_server() {
    // 1) Bind the VAO:
    /*YOUR ANSWER*/

    // 2) Bind vbo as the current VBO. Note: the VBO was created in the constructor
    /*YOUR ANSWER*/

    int offset = 0;

    printf ("Loading data onto the GPU...\n");
    // Calculate the size of the buffer we need
    int sizeBuffer = (total_vertices*3+total_normals*3+total_UVs*2+total_colors*4)*sizeof(GLfloat);

    // Tell OpenGL that this data probably won't change and is used for drawing (GL_STATIC_DRAW).
    // Do not upload any data yet (NULL), but we specify the size (sizeBuffer). We'll pass data 
    // later using glBufferSubData

    // 3) Call glBufferData and tell the GPU how big the buffer is.  Do NOT load any data yet.
    /*YOUR ANSWER*/

    // If the vertices aren't NULL, load them onto the GPU. Offset is currently 0.
    if (vertices) {
        printf ("Loading vertices onto GPU...\n");
        // Load the vertices into the GPU buffer. Note the size is the number of vertices * 3(x, y, z)
        glBufferSubData(GL_ARRAY_BUFFER, offset, total_vertices*3*sizeof(GLfloat), this->vertices);
        // You should read this as "vPosition should read in 3 GL_FLOATs that aren't normalized (GL_FALSE).
        // The data has a stride of 0 (non-interlaced) and starts with an offset of 0 in the buffer."
        glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
        offset+=total_vertices*3*sizeof(GLfloat);
    }
    // Load in the vertex normals right after the vertex coordinates.  Remember, there are 3 values for a normal
    if (normals) {
        printf ("Loading normals onto GPU...\n");

        // 4) Load in the vertex data onto the GPU using glBufferSub. Put it right after the vertices

        // Note that the normal data has an offset that starts after the vertex data in the buffer
        glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(offset));
        offset+=total_normals*3*sizeof(GLfloat);

    }
    // Load in the texture coordinates right after the normals. Remember, there are 2 values for each UV
    if (uvs) {
        printf ("Loading UVs onto GPU...\n");

        // 5) Call glBufferSubData to put the UVs onto the GPU. There are only 2 components in each UV

        // 6) Call glVertexAttribPointer to tell vTexCoord where to find it's data. 

        offset+=total_UVs*2*sizeof(GLfloat);
    }
    // Load in the color coordinates right after the texture coordinates. There are 4 values for a color
    if (colors) {
        printf ("Loading colors onto GPU...\n");

        // 7) Put the color info onto the GPU. CAREFUL! There are 4 parts to each color
        /*YOUR ANSWER*/

        // 8) Specify where the color attributes (vColor) are located
        /*YOUR ANSWER*/

        offset+=total_colors*4*sizeof(GLfloat);
    }
}

void Model::render(){
    glBindVertexArray(vao);                        // Activate the VAO again. All that buffer info is remembered
    glUseProgram(shader->program_ID);            // Use the shader program
    if (vertices) {
        glEnableVertexAttribArray(vPosition);    // It's a pain, but we always have to enable shader variables
    }
    if (normals) {
        glEnableVertexAttribArray(vNormal);
    }
    //if (vTexCoord) {//ik12/1/2013
    if (uvs) {
        glEnableVertexAttribArray(vTexCoord);
    }
    //if (vColor) {
    if (colors) {
        glEnableVertexAttribArray(vColor);
    }
    // Do the actual draw!  Remember, we've already set up the buffers on the GPU,
    // so when we call glDrawArrays, it uses the currently bound buffer; the state
    // information is held in the VAO.
    glDrawArrays(GL_TRIANGLES, 0, total_vertices);

    if (vertices) {
        glDisableVertexAttribArray(vPosition);    // Disable the variables
    }
    if (normals) {
        glDisableVertexAttribArray(vNormal);
    }
    //if (vTexCoord) {
    if (uvs) {
        glDisableVertexAttribArray(vTexCoord);
    }
    //if (vColor) {
    if (colors) {
        glDisableVertexAttribArray(vColor);
    }
}
