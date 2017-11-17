#include <glbinding/Binding.h>
#include <glbinding/gl41/gl.h>

#include <GLFW/glfw3.h>

#include "mesh.hpp"

int width = 1024;
int height = 768;

std::string windowTitle = "Transport Game Concept 2D";
std::string grassTile = "assets/models/grass_flat.obj";



int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_SAMPLES, 4);
    // OpenGL major version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // OpenGL minor version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // Enable OpenGL forward compatibility. Required on Mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // Set the OpenGL profile to the core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glbinding::Binding::initialize();



    // Set the clear colour
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it is closer to the camera then the former one
    glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    Mesh *mesh = new Mesh(grassTile);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        mesh->render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete mesh;

    glfwTerminate();
    return 0;
}