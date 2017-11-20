//
// Created by Peter Lewis on 2017-11-18.
//

#include "controls.hpp"
#include "time_manager.hpp"

#include <glm/detail/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>
#include <spdlog/spdlog.h>

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
    return ViewMatrix;
}

glm::mat4 getProjectionMatrix() {
    return ProjectionMatrix;
}

// Initialize position : on +Z
glm::vec3 position = glm::vec3(0, 0, 5);
// Initial horizontal angle : toward -z
float horizontalAngle = 3.14F;
// initial vertical angle : none
float verticalAngle = 0.0F;
// Initial FoV
float initialFoV = 45.0F;

float speed = 3.0F; // 3 units / second
float mouseSpeed = 0.005F;

bool rotateCamera;

void computeMatricesFromInputs(GLFWwindow* window, int width, int height) {
    auto deltaTime = transport::TimeManager::INSTANCE()->getDeltaTime();

    // Get mouse position
    double xpos = width / 2;
    double ypos = height / 2;
    //glfwGetCursorPos(window, &xpos, &ypos);

    // Reset mouse positioon for next frame
    //glfwSetCursorPos(window, width / 2, height / 2);

    // Compute new orientation
    horizontalAngle += mouseSpeed * float(width / 2 - xpos);
    verticalAngle   += mouseSpeed * float(height / 2 - ypos);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
            sin(horizontalAngle - 3.14F / 2.0F),
            0,
            cos(horizontalAngle - 3.14F / 2.0F)
    );

    // Up vector
    glm::vec3 up = glm::cross(right, direction);

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        position += direction * float(deltaTime) * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        position -= direction * float(deltaTime) * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        position += right * float(deltaTime) * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        position -= right * float(deltaTime) * speed;
    }

    float FoV = initialFoV;

    // Projection matrix : 45 FoV, custom calculated ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(glm::radians(FoV), float(width / height), 0.1F, 100.0F);
    // Camera matrix
    ViewMatrix = glm::lookAt(
            position,
            position + direction,
            up
    );
}

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {

}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
        rotateCamera = true;
        spdlog::get("console")->info("tilt true");
    }
    if(button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) {
        rotateCamera = false;
        spdlog::get("console")->info("tilt false");
    }
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    printf("%f %f \n", xoffset, yoffset);
}
