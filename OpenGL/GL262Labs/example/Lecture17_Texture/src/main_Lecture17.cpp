/*
 * @topic T0L173 Textures
 * @brief OpenGL client program
*/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
// Include GLM:
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "../../../common/Wavefront.h"

// main_Lecture17.cpp
// shader path configuration:
#define    BCC_PROJECT_NAME "Lecture17_Texture"
#define    BCC_ROOT_PATH "../../example/"
#define    BCC_VERTEX_SHADER BCC_ROOT_PATH BCC_PROJECT_NAME "/Shaders/vertexProgram_v.c"
#define    BCC_FRAGMENT_SHADER  BCC_ROOT_PATH BCC_PROJECT_NAME "/Shaders/fragmentProgram_f.c"

//#define BMP_FILE_PATH "../../Models/BMP/scales.bmp"
//#define BMP_FILE_PATH "../../Models/BMP/uvtemplate.bmp"
#define BMP_FILE_PATH "../../Models/BMP/numbers.bmp"

// OBJ Models that contain textture coordinates:
//------------------------------------------------------------------
// HOW TO TEST DIFFERENT MODELS:
//------------------------------------------------------------------
// Include one of the models defined in a header file,
// -or-
// load te model from the OBJ file by defining MODEL_OBJ_FILENAME
//------------------------------------------------------------------

//#include "../../../common/Objects/cube_textured.h"    // UPDATE! - look at this file if you haven't!
//#include "../../../common/Objects/triangle.h"

//#define MODEL_OBJ_FILENAME "../../Models/Spheretree/bunny-1500.obj"
//#define MODEL_OBJ_FILENAME "../../Models/Spheretree/cow-1500.obj"
//#define MODEL_OBJ_FILENAME "../../Models/Spheretree/dragon-1500.obj"  // scale_amount = 2.5f;
//#define MODEL_OBJ_FILENAME "../../Models/Spheretree/lamp600.obj"        // scale_amount = 0.007f
//#define MODEL_OBJ_FILENAME "../../Models/Spheretree/shammy.obj"          // scale_amount = 0.001f
//#define MODEL_OBJ_FILENAME "../../Models/Spheretree/teapot.obj"      // scale_amount = 0.001f

//#define MODEL_OBJ_FILENAME "../../Models/Misc/cube5.obj" // a bigger cube (5 units) -- scale_amount = 0.15f;
//#define MODEL_OBJ_FILENAME "../../Models/Misc/cube_blender.obj.txt"
//#define MODEL_OBJ_FILENAME "../../Models/Misc/plane.obj"
//#define MODEL_OBJ_FILENAME "../../Models/Misc/car.obj" // scale_amount = 0.15f;
#define MODEL_OBJ_FILENAME "../../Models/Misc/cube_textured.obj" // scale_amount = 0.5f;
//#define MODEL_OBJ_FILENAME "../../Models/Misc/triangle.obj" // scale_amount = 0.5f;
//#define MODEL_OBJ_FILENAME "../../Models/Misc/square.obj" // scale_amount = 0.5f;

#ifdef MODEL_OBJ_FILENAME
int num_vertices = 0;
int num_normals = 0;
int num_uvs = 0;
int num_indices = 0;

GLfloat* vertices = NULL;
GLfloat* normals = NULL;
GLfloat* UVs = NULL;
GLuint* indices = NULL;
#endif

#define BCC_USING_INDEX_BUFFER 1

#ifdef BCC_USING_INDEX_BUFFER
    #define NUM_VERTICES num_vertices    
    #define NUM_INDICES num_indices    
#else
    #define NUM_VERTICES num_vertices
#endif

// From http://www.opengl.org/registry/specs/EXT/pixel_buffer_object.txt 
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

GLfloat light[] = {0.0f, 1.0f, 1.0f, 1.0f};

GLuint shader_program_ID;
GLuint vao = 0;
GLuint vbo;
GLuint position_ID, normal_ID; 
GLuint index_buffer_ID; 

GLuint    perspective_matrix_ID, view_matrix_ID, model_matrix_ID;    // IDs of variables mP, mV and mM in the shader
GLuint    all_rotations_matrix_ID; 
GLuint    light_ID;        

//========== UPDATE! ================================
GLuint     tex_buffer_ID;    // We have to create a buffer to hold the image. However, it WON'T go in the vertex buffer
GLuint     tex_coord_ID;    // The ID of the "texCoord" variable in the shader
GLuint     texture_ID;            // The ID of the "texture" variable in the shader
GLubyte* image_data;        // This will contain the raw color information from the file
//=================================================

// Initialize matrices to the Identity matrix
glm::mat4 mtx_rot_Y = glm::mat4( 1.0f );    // Matrix for rotations about the Y axis
glm::mat4 mtx_trans = glm::mat4( 1.0f );    // Matrix for changing the position of the object
glm::mat4 mtx_scale = glm::mat4( 1.0f );
glm::mat4 mtx_M = glm::mat4( 1.0f );                // The final model matrix to change into world coordinates

glm::mat4 mtx_all_rots = glm::mat4( 1.0f );    // UPDATE - we keep all of the model's rotations in this matrix (for rotating normals)

glm::mat4 mtx_V = glm::mat4( 1.0f );                // The camera matrix (for position/rotation) to change into camera coordinates
glm::mat4 mtx_P = glm::mat4( 1.0f );                // The perspective matrix for the camera (to give the scene depth); initialize this ONLY ONCE!

GLfloat  theta;            // An amount of rotation along one axis
GLfloat     scale_amount;    // In case the object is too big or small

GLfloat camX, camY, camZ;    // A first attempt at camera movement
GLfloat yaw, pitch, roll;    // Store this in a matrix instead!


// Header info found at http://atlc.sourceforge.net/bmp.html
void load_bmp_file(const char* filename, int* width, int* height, int* size, unsigned char** pixel_data) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf ("Couldn't open file... aborting\n");
        assert( !filename );
        exit( 1 );
    }
    short identifier = -1;
    fread(&identifier, 1, sizeof(short), fp); printf ("Identifer is: %c\n", identifier);
    int filesize = -1;
    fread(&filesize, 1, sizeof(int), fp); printf ("filesize is: %d\n", filesize);
    int reserved = -1;
    fread(&reserved, 1, sizeof(int), fp); printf ("reserved is: %d\n", reserved);
    int bitmap_offset = -1;
    fread(&bitmap_offset, 1, sizeof(int), fp); printf ("bitmap_offset is: %d\n", bitmap_offset);
    int bitmap_header_size = -1;
    fread(&bitmap_header_size, 1, sizeof(int), fp); printf ("bitmap_header_size is: %d\n", bitmap_header_size);
    int bitmap_width = -1;
    fread(&bitmap_width, 1, sizeof(int), fp); printf ("bitmap_width is: %d\n", bitmap_width);
    int bitmap_height = -1;
    fread(&bitmap_height, 1, sizeof(int), fp); printf ("bitmap_height is: %d\n", bitmap_height);
    short bitmap_planes = -1;
    fread(&bitmap_planes, 1, sizeof(short), fp); printf ("bitmap_planes is: %d\n", bitmap_planes);
    short bits_per_pixel= -1;
    fread(&bits_per_pixel, 1, sizeof(short), fp); printf ("bits_per_pixel is: %d\n", bits_per_pixel);
    int compression = -1;
    fread(&compression, 1, sizeof(int), fp); printf ("compression is: %d\n", compression);
    int bitmap_data_size = -1;
    fread(&bitmap_data_size, 1, sizeof(int), fp); printf ("bitmap_data_size is: %d\n", bitmap_data_size);
    int hresolution = -1;
    fread(&hresolution, 1, sizeof(int), fp); printf ("hresolution is: %d\n", hresolution);
    int vresolution = -1;
    fread(&vresolution, 1, sizeof(int), fp); printf ("vresolution is: %d\n", vresolution);
    int num_colors = -1;
    fread(&num_colors, 1, sizeof(int), fp); printf ("num_colors is: %d\n", num_colors);
    int num_important_colors = -1;
    fread(&num_important_colors, 1, sizeof(int), fp); printf ("num_important_colors is: %d\n", num_important_colors);
    
    // Jump to the data already!
    fseek (fp, bitmap_offset, SEEK_SET);
    unsigned char* data = new unsigned char[bitmap_data_size];
    // Read data in BGR format
    fread (data, sizeof(unsigned char), bitmap_data_size, fp);
    
    // Make pixel_data point to the pixels
    *pixel_data = data;
    *size = bitmap_data_size;
    *width = bitmap_width;
    *height = bitmap_height;
    fclose(fp);
}


void init_global_data() {

    theta = 0.0f;
    scale_amount = 1.0f;

    // Set up the P_erspective matrix only once!
    // Arguments are
    // 1) FoV,
    // 2) aspect ratio,
    // 3) near plane
    // 4) far plane
    mtx_P = glm::perspective( 60.0f, 1.0f, 1.0f, 1000.0f );
}

// Begin shader functions
static char* load_text_file(const char* filename) {
    // Open the file
    FILE* fp = fopen (filename, "r");
    // Move the file pointer to the end of the file and determing the length
    fseek(fp, 0, SEEK_END);
    long file_length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* contents = new char[file_length+1];
    // zero out memory
    for (int i = 0; i < file_length+1; i++) {
        contents[i] = 0;
    }
    // Here's the actual read
    fread (contents, 1, file_length, fp);
    // This is how you denote the end of a string in C
    contents[file_length] = '\0';
    fclose(fp);
    return contents;
}

bool is_shader_compiled_okay(GLint shader_ID){
    GLint compiled = 0;
    glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &compiled);
    if (compiled) {
        return true;
    }
    else {
        GLint log_length;
        glGetShaderiv(shader_ID, GL_INFO_LOG_LENGTH, &log_length);
        char* msg_buffer = new char[log_length];
        glGetShaderInfoLog(shader_ID, log_length, NULL, msg_buffer);
        printf ("%s\n", msg_buffer);
        delete[] (msg_buffer);
        return false;
    }
}

GLuint compile_vertex_shader(const char* shader_source) {
    GLuint vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource (vertex_shader_ID, 1, (const GLchar**)&shader_source, NULL);
    glCompileShader(vertex_shader_ID);
    bool compiled_correctly = is_shader_compiled_okay(vertex_shader_ID);
    if (compiled_correctly) {
        return vertex_shader_ID;
    }
    return -1;
}

GLuint compile_fragment_shader(const char* shader_source) {
    GLuint fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_ID, 1, (const GLchar**)&shader_source, NULL);
    glCompileShader(fragment_shader_ID);
    bool compiled_correctly = is_shader_compiled_okay(fragment_shader_ID);
    if (compiled_correctly) {
        return fragment_shader_ID;
    }
    return -1;
}

GLuint link_shader_program (GLuint vertex_shader_ID, GLuint fragment_shader_ID) {
    GLuint shader_ID = glCreateProgram();
    glAttachShader(shader_ID, vertex_shader_ID);
    glAttachShader(shader_ID, fragment_shader_ID);
    glLinkProgram(shader_ID);
    return shader_ID;
}
// End shader functions

// Any time the window is resized, this function gets called. Set by the
// "glutReshapeFunc" in main.
void change_viewport(int w, int h){
    glViewport(0, 0, w, h);
}

void keyboard_down (unsigned char key, int x, int y) {
    switch (key) {
        case 033:
        case 'q':
            exit(1);
            break;
        case 'w': camZ += 0.1f; break;
        case 's': camZ -= 0.1f; break;
        case 'a': camX += 0.1f; break;
        case 'd': camX -= 0.1f; break;
        case 'e': yaw += 0.05f; break;
        case 'r': yaw -= 0.05f; break;

        case 'Y': camY += 0.1f; break;
        case 'y': camY -= 0.1f; break;
    }
}

void animate()
{
    glutPostRedisplay();
}

// Here is the function that gets called each time the window needs to be redrawn.
// It is the "paint" function for our program, and is set up from the glutDisplayFunc in main
void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_program_ID);
    theta+= 0.01f;
    scale_amount = 0.5f; //sin(theta);
    //scale_amount = 0.001f;

    // Set the M_odel matrix
    mtx_scale = glm::scale(  // Scale first
        glm::mat4( 1.0f ),
        glm::vec3( scale_amount, scale_amount, scale_amount )
        );
    mtx_rot_Y = glm::rotate(
        glm::mat4( 1.0f ),
        glm::degrees( theta ),
        glm::vec3(0.0f, 1.0f, 0.0f)
        );
    mtx_trans = glm::translate(
        glm::mat4( 1.0f ),
        glm::vec3( 0.0f, 0.0f, -2.0f )
        );
    // Set the M_odel matrix
    mtx_M = mtx_trans * mtx_rot_Y * mtx_scale;
    
    // Copy the rotations into the mtx_all_rots
    mtx_all_rots = mtx_rot_Y;
    // UPDATE! Change the V_iew matrix if you want to "move" around the scene
    mtx_rot_Y = glm::rotate(
        glm::mat4( 1.0f ),
        glm::degrees( yaw ),
        glm::vec3(0.0f, 1.0f, 0.0f)
        );

    mtx_trans = glm::translate(
        glm::mat4( 1.0f ),
        glm::vec3( camX, camY, camZ )
        );

    mtx_V = mtx_rot_Y * mtx_trans;
    
    // Upload data to the shader variables
    glUniformMatrix4fv(model_matrix_ID, 1, GL_FALSE, glm::value_ptr( mtx_M ) );
    glUniformMatrix4fv(view_matrix_ID, 1, GL_FALSE, glm::value_ptr( mtx_V ) );
    glUniformMatrix4fv(perspective_matrix_ID, 1, GL_FALSE, glm::value_ptr( mtx_P ) );
    glUniformMatrix4fv(all_rotations_matrix_ID, 1, GL_FALSE, glm::value_ptr( mtx_all_rots ) );
    glUniform4fv(light_ID, 1, light);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#ifdef BCC_USING_INDEX_BUFFER
    glDrawElements (GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, NULL);
#else
    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
#endif
    glutSwapBuffers();
}

int main (int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Texture Mapping");
    glutReshapeFunc(change_viewport);
    glutKeyboardFunc(keyboard_down);
    glutDisplayFunc(render);
    glutIdleFunc( animate );
    if (GLEW_OK != glewInit() ) {
        assert( !"glewInit() has failed!" );
        exit(1);
    }

    init_global_data(); 

    // Make a shader
    char* cstr_vertex_shader_source = load_text_file( BCC_VERTEX_SHADER );
    char* cstr_fragment_shader_source = load_text_file( BCC_FRAGMENT_SHADER );
    GLuint vert_shader_ID = compile_vertex_shader(cstr_vertex_shader_source);
    GLuint frag_shader_ID = compile_fragment_shader(cstr_fragment_shader_source);
    shader_program_ID = link_shader_program(vert_shader_ID, frag_shader_ID);

    // Generate vertex array object names
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

#ifdef MODEL_OBJ_FILENAME
    WavefrontObjLoader loader( MODEL_OBJ_FILENAME );
    if ( !loader.load() ) {
        std::cout << "Failed to load OBJ file, exiting!" << std::endl;
        return 1;
    }
    num_vertices = loader.num_vertices;
    num_normals = loader.num_normals;
    num_uvs = loader.num_uvs;
    num_indices = loader.num_indices;
    vertices = loader.vertices;
    normals = loader.normals;
    UVs = loader.UVs;
    indices = loader.indices;
#endif

    // ========= UPDATE! =============================
    // We have 8 pieces of data: position (x, y, z), normal (x, y, z), UV (s, t)
    // Create the buffer, but don't load anything yet
    glBufferData(GL_ARRAY_BUFFER, 8*NUM_VERTICES*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    
    // Load the vertex points
    glBufferSubData(GL_ARRAY_BUFFER, 0, 3*NUM_VERTICES*sizeof(GLfloat), vertices);
    // Load the colors right after that 
    glBufferSubData(GL_ARRAY_BUFFER, 3*NUM_VERTICES*sizeof(GLfloat),3*NUM_VERTICES*sizeof(GLfloat), normals);
    // UPDATE! Load the UVs right after that
    glBufferSubData(GL_ARRAY_BUFFER, 6*NUM_VERTICES*sizeof(GLfloat),2*NUM_VERTICES*sizeof(GLfloat), UVs);
    
    
#ifdef BCC_USING_INDEX_BUFFER
    glGenBuffers(1, &index_buffer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUM_INDICES*sizeof(GLuint), indices, GL_STATIC_DRAW);
#endif
    
    // Find the position of the variables in the shader
    position_ID = glGetAttribLocation(shader_program_ID, "s_vPosition");
    normal_ID = glGetAttribLocation(shader_program_ID, "s_vNormal");
    light_ID = glGetUniformLocation(shader_program_ID, "vLight");    

    //=============== UPDATE! ==================================
    int bmpWidth = -1;
    int bmpHeight = -1;
    int bmpSize = -1;
    load_bmp_file( BMP_FILE_PATH, &bmpWidth, &bmpHeight, &bmpSize, (unsigned char**)&image_data);

    glEnable (GL_TEXTURE_2D);                    // Turn on texturing
    glGenTextures(1, &tex_buffer_ID);                // Create an ID for a texture buffer
    glBindTexture (GL_TEXTURE_2D, tex_buffer_ID);    // Bind that buffer so we can then fill it (in next line)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpWidth, bmpHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, image_data);

    tex_coord_ID = glGetAttribLocation(shader_program_ID, "s_vTexCoord");
    glEnableVertexAttribArray(tex_coord_ID);
    int texture_coord_offset = 6*NUM_VERTICES*sizeof(GLfloat);
    glVertexAttribPointer(tex_coord_ID, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(texture_coord_offset));

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);    // Set the preferences
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    texture_ID = glGetUniformLocation(shader_program_ID, "texture");
    glActiveTexture(GL_TEXTURE0);                // Turn on texture unit 0
    glUniform1i(texture_ID, 0);                        // Tell "s_vTexCoord" to use the 0th texture unit

    //======================================================


    // ============ glUniformLocation is how you pull IDs for uniform variables===============
    perspective_matrix_ID = glGetUniformLocation(shader_program_ID, "mP");
    view_matrix_ID = glGetUniformLocation(shader_program_ID, "mV");
    model_matrix_ID = glGetUniformLocation(shader_program_ID, "mM");
    all_rotations_matrix_ID = glGetUniformLocation(shader_program_ID, "mRotations");
    
    glVertexAttribPointer(position_ID, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(normal_ID, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SIZEOF_VERTICES_IN_BYTES( 3, NUM_VERTICES )));
    
    glUseProgram(shader_program_ID);
    glEnableVertexAttribArray(position_ID);
    glEnableVertexAttribArray(normal_ID);
    
    // Turn on depth culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); 
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
    
    return 0;
}