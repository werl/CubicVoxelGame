//
// Created by Peter Lewis on 2017-11-18.
//

#ifndef CUBICVOXELGAME_CONTROLS_HPP
#define CUBICVOXELGAME_CONTROLS_HPP

#include <GLFW/glfw3.h>
#include <glm/detail/type_mat.hpp>

void computeMatricesFromInputs(GLFWwindow* window);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
void windowResizeCallback(GLFWwindow* window, int x, int y);

#endif //CUBICVOXELGAME_CONTROLS_HPP
