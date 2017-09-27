#include <GL/glew.h>
#include <GL/freeglut.h> 
#include "Shader.h"
#include "Model.h"

// c262_lab03.cpp
// shader path configuration:
#define    BCC_PROJECT_NAME "c262_lab03"
#define    BCC_ROOT_PATH "../../labs/"
#define    BCC_VERTEX_SHADER BCC_ROOT_PATH BCC_PROJECT_NAME "/Shaders/vertexShader_v.c"
#define    BCC_FRAGMENT_SHADER  BCC_ROOT_PATH BCC_PROJECT_NAME "/Shaders/fragmentShader_f.c"

Model* myModel;

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // More things to do -- glPolygonMode:
    /*YOUR ANSWER*/
    myModel->render();
    glutSwapBuffers();
}

// Any time the window is resized, this function gets called. Set by the
// "glutReshapeFunc" in main.
void change_viewport(int w, int h){
    glViewport(0, 0, w, h);
}

int main (int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);

    // Set up some memory buffers for our display
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    // Set the window size
    glutInitWindowSize(800, 600);
    // Create the window with the title "Triangle"
    glutCreateWindow("Buffer Lab");
    // Bind the two functions (above) to respond when necessary
    glutReshapeFunc(change_viewport);
    glutDisplayFunc(render);

    // Remember, we always init GLEW after we create a window
    // This asks the GPU driver for all of those gl functions
    if (GLEW_OK != glewInit()) {
        exit(1);
    }
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    Shader* myShader = new Shader(BCC_VERTEX_SHADER, BCC_FRAGMENT_SHADER);

    myModel = new Model(myShader);

    GLfloat vertices[] = {-0.5f, -0.5f, 0.0f, 
                           0.5f, -0.5f, 0.0f, 
                           0.0f, 0.5f, 0.0f};

    GLfloat colors[] = {1.0f, 0.0f, 0.0f, 1.0f, 
                        0.0f, 1.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f, 1.0f};

    // 1) Try different geometry from the lab handout:
    /*YOUR ANSWER*/

    myModel->set_geometry(vertices, sizeof (vertices));
    myModel->set_vertex_colors(colors, sizeof (colors));
    myModel->upload_2_server();

    glutMainLoop();


    return 0;
}
