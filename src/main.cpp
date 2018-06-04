#include <glbinding/gl41/gl.h>
#include <glbinding/Binding.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "time_manager.hpp"
#include "constants.hpp"
#include "mesh.hpp"
#include "program.hpp"
#include "controls.hpp"
#include "tile_base.hpp"
#include "tile_grass.hpp"
#include "registry.hpp"
#include "world.hpp"

namespace spd = spdlog;
using namespace gl;

std::string windowTitle = "Transport Game Concept 2D";
std::string grassTile = "assets/models/road_turn.obj";

int main() {
    constants::RUN_GL_TESTS = true;

    auto console = spd::stdout_color_st("console");

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        console->error("GLFW didn't initialize");
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_SAMPLES, 1);
    // OpenGL major version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    // OpenGL minor version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    // Enable OpenGL forward compatibility. Required on Mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    // Set the OpenGL profile to the core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(constants::width, constants::height, windowTitle.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        console->error("GLFW window couldn't be created");
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glbinding::Binding::initialize();

    // Set mouse at the center of  the screen
    glfwPollEvents();
    glfwSetCursorPos(window, constants::width/2, constants::height/2);
    //glfwSwapInterval(1);


    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
    // Set the clear colour
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it is closer to the camera then the former one
    glDepthFunc(GL_LESS);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    Program *program = new Program("simple_program", "assets/shaders/simple_vertex.glsl", "assets/shaders/simple_fragment.glsl");

    if(!program->isProgramSuccess()) {
        return 2;
    }

    Mesh *mesh = new Mesh(grassTile);
    //mesh->setProgram(program->getProgramID());
    auto *tile = new tile::TileGrass();

    registerTileAndMesh(*tile, *mesh, "grass");
    world::World world1(10, 10);

    GLint MatrixID = glGetUniformLocation(program->getProgramID(), "MVP");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        transport::TimeManager::INSTANCE()->beginFrame();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Ignore if there is an error here, works fine!

        program->useProgram();

        computeMatricesFromInputs(window);
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;

        gl::glUniformMatrix4fv(MatrixID, 1, gl::GL_FALSE, &mvp[0][0]);

        world1.render(program);

        program->detachProgram();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete program;

    glfwTerminate();
    return 0;
}