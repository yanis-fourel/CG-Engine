/*
** EPITECH PROJECT, 2019
** Project
** File description:
** AppWindow.cpp
*/

#include <stdexcept>
#include <iostream>
#include <GL/glew.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "CG/AppWindow.hpp"

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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init();
}

AppWindow::~AppWindow()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool AppWindow::run()
{
	if (m_firstFrame)
		m_firstFrame = false;
	else
		onFrameEnd();

	onFrameBegin();

	processInputs();
	if (glfwWindowShouldClose(m_window))
		return false;

	return true;
}

void AppWindow::onFrameBegin()
{
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void AppWindow::onFrameEnd()
{
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(m_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(m_window);
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
	if (isKeyDown(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(m_window, true);

	if (m_captureMouse) {
		glfwGetCursorPos(m_window, &m_mouseMovement.x, &m_mouseMovement.y);
		glfwSetCursorPos(m_window, 0, 0);
	}
	else {
		m_mouseMovement = { 0, 0 };
	}
}
