#include <stdexcept>
#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "CG/Window.hpp"

CG::Window::Window(const CG::Vector2 windowSize, const std::string &windowName)
{
	if (!glfwInit())
		throw std::runtime_error("Failed to init glfw");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y), windowName.c_str(), nullptr, nullptr);
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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

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

auto CG::Window::pointToNormalized(const CG::Vector2 &pixelPos) const noexcept -> CG::Vector2  
{
	CG::Vector2 ratio_0_1(pixelPos / getSize());

	// Prevent out of range if cursor is out of the window
	ratio_0_1.x = std::clamp<decltype(ratio_0_1)::value_type>(ratio_0_1.x, 0, 1);
	ratio_0_1.y = std::clamp<decltype(ratio_0_1)::value_type>(ratio_0_1.y, 0, 1);

	return ratio_0_1 * 2 - Vector2(1, 1);
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

