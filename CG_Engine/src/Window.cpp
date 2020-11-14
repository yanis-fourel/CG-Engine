#include <stdexcept>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "CG/Window.hpp"

CG::Window::Window()
{
	if (!glfwInit())
		throw std::runtime_error("Failed to init glfw");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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
			+ (const char *)glewGetErrorString(
				glewInitResult));

	}

	glEnable(GL_DEPTH_TEST);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init();
}

CG::Window::~Window()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool CG::Window::run()
{
	if (m_firstFrame)
		m_firstFrame = false;
	else
		onFrameEnd();

	onFrameBegin();

	if (glfwWindowShouldClose(m_window))
		return false;

	return true;
}

void CG::Window::close() noexcept
{
	glfwSetWindowShouldClose(m_window, true);
}

auto CG::Window::getSize() const noexcept -> CG::Vector2
{
	int display_w, display_h;
	glfwGetFramebufferSize(m_window, &display_w, &display_h);

	return {
		static_cast<CG::Vector2::value_type>(display_w),
		static_cast<CG::Vector2::value_type>(display_h)
	};
}

void CG::Window::onFrameBegin()
{
	glfwPollEvents();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CG::Window::onFrameEnd()
{
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(m_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(m_window);
}
