/*
 * @topic T0L083 Index Buffers
 * @brief OpenGL client program
*/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>

// main_Lecture08.cpp
// shader path configuration:
#define    BCC_PROJECT_NAME "Lecture08_Index"
#define    BCC_ROOT_PATH "../../example/"
#define    BCC_VERTEX_SHADER BCC_ROOT_PATH BCC_PROJECT_NAME "/Shaders/vertexProgram_v.c"
#define    BCC_FRAGMENT_SHADER  BCC_ROOT_PATH BCC_PROJECT_NAME "/Shaders/fragmentProgram_f.c"

#define BCC_USING_INDEX_BUFFER 1

#ifdef BCC_USING_INDEX_BUFFER
    #define NUM_VERTICES 6
    #define NUM_INDICES 9    
#else
    #define NUM_VERTICES 9
#endif


#define BUFFER_OFFSET(i) ((char *)NULL + (i))
GLuint shader_program_ID;
GLuint vao = 0;
GLuint vbo;
GLuint position_ID, colorID;
GLuint index_buffer_ID;

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

// Here is the function that gets called each time the window needs to be redrawn.
// It is the "paint" function for our program, and is set up from the glutDisplayFunc in main
void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
    glutCreateWindow("Index Buffers");
    glutReshapeFunc(change_viewport);
    glutDisplayFunc(render);
    glewInit();

#ifdef BCC_USING_INDEX_BUFFER
    GLfloat vertices[] = {0.0f, 0.5f, 0.0f, // 0
                        -0.25f, 0.0f, 0.0f, // 1
                        0.25f, 0.0f, 0.0f, // 2
                        -0.5f, -0.5f, 0.0f, // 3
                        0.0f, -0.5f, 0.0f, // 4
                        0.5f, -0.5f, 0.0f // 5
    };
    GLfloat colors[] = {1.0f, 0.00f, 0.0f, 1.0f, // 0
                        0.0f, 1.00f, 0.0f, 1.0f, // 1
                        0.0f, 0.00f, 1.0f, 1.0f, // 2
                        0.0f, 0.00f, 1.0f, 1.0f, // 3
                        1.0f, 0.00f, 0.0f, 1.0f, // 4
                        0.0f, 1.0f, 0.0f, 1.0f // 5
    };
    
    GLuint indices[] = {0, 1, 2, 1, 3, 4, 2, 4, 5};
#else
    GLfloat vertices[] = {-0.5f, -0.5f, 0.0f, 
                        0.0f, -0.5f, 0.0f, 
                        -0.25f, 0.0f, 0.0f,
                        -0.25f, 0.0f, 0.0f,
                        0.25f, 0.0f, 0.0f,
                        0.0f, 0.5f, 0.0f,
                        0.0f, -0.5f, 0.0f,
                        0.5f, -0.5f, 0.0f,
                        0.25f, 0.0f, 0.0f
    };
    GLfloat colors[] = {1.0f, 0.00f, 0.0f, 1.0f, 
                        0.0f, 1.00f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f, 1.0f,
                        1.0f, 0.00f, 0.0f, 1.0f, 
                        0.0f, 1.00f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f, 1.0f,
                        1.0f, 0.00f, 0.0f, 1.0f, 
                        0.0f, 1.00f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f, 1.0f
    };
    
#endif

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
    // Create the buffer, but don't load anything yet
    glBufferData(GL_ARRAY_BUFFER, 7*NUM_VERTICES*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    // Load the vertex points
    glBufferSubData(GL_ARRAY_BUFFER, 0, 3*NUM_VERTICES*sizeof(GLfloat), vertices); 
    // Load the colors right after that
    glBufferSubData(GL_ARRAY_BUFFER, 3*NUM_VERTICES*sizeof(GLfloat),4*NUM_VERTICES*sizeof(GLfloat), colors);

#ifdef BCC_USING_INDEX_BUFFER
    glGenBuffers(1, &index_buffer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUM_INDICES*sizeof(GLuint), indices, GL_STATIC_DRAW);
#endif
    
    // Find the position of the variables in the shader
    position_ID = glGetAttribLocation(shader_program_ID, "s_vPosition");
    colorID = glGetAttribLocation(shader_program_ID, "s_vColor");

    glVertexAttribPointer(position_ID, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));
    glUseProgram(shader_program_ID);
    glEnableVertexAttribArray(position_ID);
    glEnableVertexAttribArray(colorID);
    
    glutMainLoop();
    
    return 0;
}