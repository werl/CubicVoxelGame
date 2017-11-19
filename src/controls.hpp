//
// Created by Peter Lewis on 2017-11-18.
//

#ifndef TRANSPORTCONCEPT2D_CONTROLS_HPP
#define TRANSPORTCONCEPT2D_CONTROLS_HPP

#include <GLFW/glfw3.h>
#include <glm/detail/type_mat.hpp>

void computeMatricesFromInputs(GLFWwindow* window, int width, int height);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

#endif //TRANSPORTCONCEPT2D_CONTROLS_HPP
