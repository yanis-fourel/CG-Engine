/*
** EPITECH PROJECT, 2019
** Project
** File description:
** AppWindow.hpp
*/

#pragma once

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

class AppWindow
{
public:
    AppWindow();
    ~AppWindow();

    bool run();

    bool isKeyDown(int key);
    glm::vec2 getMouseMovemement();
private:
    void processInputs();

private:
    GLFWwindow *m_window;
    bool m_firstFrame = true;

    glm::vec<2, double> m_mouseMovement {0, 0};
};


