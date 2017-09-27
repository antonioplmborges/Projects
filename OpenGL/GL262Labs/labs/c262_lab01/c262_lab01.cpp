#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

GLuint triangle_vao;
GLint vertexID;
GLint fragID;
GLuint shader;


// This function asks the driver for a vertex array object, which will store information
// about what is being drawn, such as geometry, color information, texture information and so on.
// Hold on to the ID that this function returns, because you can use it later on!
GLuint create_vertex_array() {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}

// This function takes in a vertex array object ID and an array of vertices. It should be called 
// immediately after calling create_vertex_array.  It returns a buffer ID (which you probably won't
// use).  NOTE: this assumes that you want triangles and not points or lines.
GLuint upload_vertex_positions(GLuint shader_program_ID, GLuint vao, GLfloat* vVerts, GLuint total_vertices) {
    glBindVertexArray(vao);
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer (GL_ARRAY_BUFFER, buffer);
    
    // Copy the array data into the active OpenGL buffer
    glBufferData(GL_ARRAY_BUFFER, total_vertices*3*sizeof(GLfloat), vVerts, GL_STATIC_DRAW);
    
    // Figure out where vPosition is in our shader
    GLuint loc = glGetAttribLocation(shader_program_ID, "vPosition");
    // Turn it on
    glEnableVertexAttribArray(loc);
    // Tell it how the data should be parsed
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, 0);

    return buffer;
}

// You shouldn't have to call this function (it's called from the functions
// that make shaders); it is a helper function to determine if a shader compiled correctly.
int is_shader_compiled_okay(GLint shader_ID){
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

// This function takes in the source code for a vertex shader,
// compiles it, and returns the ID (number) of the shader. It returns
// -1 if the shader didn't compile
GLint compile_vertex_shader (char* shader_source) {
    GLint vShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource (vShaderID, 1, (const GLchar**)&shader_source, NULL);
    glCompileShader(vShaderID);
    int compiled_correctly = is_shader_compiled_okay(vShaderID);
    if (compiled_correctly) {
        return vShaderID;
    }
    return -1;
}

// This function takes in the source code for a fragment shader,
// compiles it, and returns the ID (number) of the shader. It returns
// -1 if the shader didn't compile
GLuint compile_fragment_shader (char* shader_source) {
    GLint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource (fShaderID, 1, (const GLchar**)&shader_source, NULL);
    glCompileShader(fShaderID);
    int compiled_correctly = is_shader_compiled_okay(fShaderID);
    if (compiled_correctly) {
        return fShaderID;
    }
    return -1;
}

// A helper function that takes in a program ID and returns whether
// or not it linked correctly.  If not, it prints out an error
// message letting you know what the problem was. This will
// be called from link_shader_program()
bool is_linked_shader_okay(GLint program_ID){
    GLint linked = 0;
    glGetProgramiv(program_ID, GL_LINK_STATUS, &linked);
    if (linked) {
        return true;
    }
    else {
        GLint log_length;
        glGetProgramiv(program_ID, GL_INFO_LOG_LENGTH, &log_length);
        char* msg_buffer = new char[log_length];
        glGetProgramInfoLog(program_ID, log_length, NULL, msg_buffer);
        printf ("%s\n", msg_buffer);
        delete[] (msg_buffer);
        return false;
    }
}

// A function that takes in the IDs for vertex and fragment shader,
// and returns the ID of a shader program that has been linked.
GLint link_shader_program (GLint vertex_shader_ID, GLint fragment_shader_ID) {
    printf ("Linking %d with %d\n", vertex_shader_ID, fragment_shader_ID);
    GLuint program_ID = glCreateProgram();
    glAttachShader(program_ID, vertex_shader_ID);
    glAttachShader(program_ID, fragment_shader_ID);
    glLinkProgram (program_ID);

    bool linked = is_linked_shader_okay (program_ID);

    if (linked) {
        return program_ID;
    }
    return -1;
}

// Any time the window is resized, this function gets called. Set by the
// "glutReshapeFunc" in main.
void change_viewport(int w, int h){
    glViewport(0, 0, w, h);
}

// Here is the function that gets called each time the window needs to be redrawn.
// It is the "paint" function for our program, and is set up from the glutDisplayFunc in main
void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glutSwapBuffers();
}

int main (int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set up some memory buffers for our display
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    // Set the window size
    glutInitWindowSize(800, 600);
    // Create the window with the title "Triangle"
    glutCreateWindow("Triangle");
    // Bind the two functions (above) to respond when necessary
    glutReshapeFunc(change_viewport);
    glutDisplayFunc(render);

    // Very important!  This initializes the entry points in the OpenGL driver so we can 
    // call all the functions in the API.
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW error");
        return 1;
    }

    char* vertex_program =
        "#version 150\n\n\
        in vec4 vPosition;\n\n\
        void main () {\n\
        \tgl_Position = vPosition;\n\
        }\n"
        ;

    char* fragment_program =
        "#version 150\n\n\
        out vec4 fColor;\n\n\
        void main () {\n\
        \tfColor = vec4 (1.0, 0.0, 0.0, 1.0);\n\
        }\n"
        ;

    float vertices[] = {-0.5f, -0.5f, 0.0f, 
                        0.5f, -0.5f, 0.0f,
                        0.0f, 0.5f, 0.0f};

    vertexID = compile_vertex_shader (vertex_program);
    fragID = compile_fragment_shader (fragment_program);
    shader = link_shader_program(vertexID, fragID);

    glUseProgram (shader);

    cout << "Vertex ID is " << vertexID << endl;
    cout << "Fragment ID is " << fragID << endl;
    cout << "Shader program ID is " << shader << endl;

    triangle_vao = create_vertex_array();
    upload_vertex_positions(shader, triangle_vao, vertices, 3);

    // Start up a loop that runs in the background (you never see it).
    glutMainLoop();
    return 0;
}
