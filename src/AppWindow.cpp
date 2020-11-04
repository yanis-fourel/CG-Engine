/*
** EPITECH PROJECT, 2019
** Project
** File description:
** AppWindow.cpp
*/

#include <stdexcept>
#include <iostream>
#include <GL/glew.h>
#include "AppWindow.hpp"

AppWindow::AppWindow()
{
	if (!glfwInit())
		throw std::runtime_error("Failed to init glfw");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!m_window) {
		glfwTerminate();
		throw std::runtime_error("Failed to create window");
	}
	glfwMakeContextCurrent(m_window);

	std::cout << "OpenGl version : " << glGetString(GL_VERSION) << std::endl;

	auto glewInitResult = glewInit();
	if (glewInitResult != GLEW_OK) {
		glfwTerminate();

		throw std::runtime_error(std::string("glewInit")
			+ (const char*)glewGetErrorString(
				glewInitResult));

	}

	glEnable(GL_DEPTH_TEST);

	if (glfwRawMouseMotionSupported()) {
		glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
}

AppWindow::~AppWindow()
{
	glfwTerminate();
}

bool AppWindow::run()
{
	if (m_firstFrame)
		m_firstFrame = false;
	else {
		int w, h;
		glfwGetFramebufferSize(m_window, &w, &h);
		glViewport(0, 0, w, h);

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
	processInputs();
	if (glfwWindowShouldClose(m_window))
		return false;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return true;
}

bool AppWindow::isKeyDown(int key)
{
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}

glm::vec2 AppWindow::getMouseMovemement()
{
	return m_mouseMovement;
}

void AppWindow::processInputs()
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);

	glfwGetCursorPos(m_window, &m_mouseMovement.x, &m_mouseMovement.y);
	glfwSetCursorPos(m_window, 0, 0);
}
