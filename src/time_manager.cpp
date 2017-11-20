//
// Created by Peter Lewis on 2017-11-19.
//

#include <GLFW/glfw3.h>

#include "time_manager.hpp"

double lastTime;
double currentTime;
double deltaTime;

transport::TimeManager::TimeManager() {
    lastTime = glfwGetTime();
    currentTime = glfwGetTime();
    deltaTime = 0;
}

transport::TimeManager* transport::TimeManager::INSTANCE() {
    static auto *timeManager = new TimeManager;
    return timeManager;
}

double transport::TimeManager::getDeltaTime() {
    return deltaTime;
}

void transport::TimeManager::beginFrame() {
    lastTime = currentTime;
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
}
