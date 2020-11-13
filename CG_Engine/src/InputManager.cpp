#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include "CG/InputManager.hpp"

CG::InputManager::InputManager(GLFWwindow *window) : m_window(window)
{}

void CG::InputManager::update()
{
	if (m_captureMouse) {
		glfwGetCursorPos(m_window, &m_mouseMovement.x, &m_mouseMovement.y);
		glfwSetCursorPos(m_window, 0, 0);
	}
	else {
		m_mouseMovement = { 0, 0 };
	}
}

bool CG::InputManager::isKeyDown(int key) const noexcept
{
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}

glm::vec2 CG::InputManager::getMouseMovement() const noexcept
{
	return m_mouseMovement;
}

void CG::InputManager::setMouseCapture(bool enabled) noexcept
{
	m_captureMouse = enabled;
}

void CG::InputManager::toggleMouseCapture() noexcept
{
	m_captureMouse = !m_captureMouse;
	spdlog::info("mouse capture toggle");
}
