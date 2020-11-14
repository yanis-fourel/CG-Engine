#include <spdlog/spdlog.h>

#include "CG/InputManager.hpp"

CG::InputManager::InputManager(GLFWwindow *window) : m_window(window)
{
	setMouseCapture(true);
}

void CG::InputManager::update()
{
	if (m_captureMouse) {
		int w, h;
		glfwGetWindowSize(m_window, &w, &h);

		double x, y;
		glfwGetCursorPos(m_window, &x, &y);
		m_mouseMovement.x = static_cast<Vector2::value_type>(x - w * 0.5);
		m_mouseMovement.y = static_cast<Vector2::value_type>(y - h * 0.5);

		resetCursorPos();
	}
	else {
		m_mouseMovement = { 0, 0 };
	}
}

bool CG::InputManager::isKeyDown(int key) const noexcept
{
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}

CG::Vector2 CG::InputManager::getMouseMovement() const noexcept
{
	return m_mouseMovement;
}

void CG::InputManager::setMouseCapture(bool enabled) noexcept
{
	m_captureMouse = enabled;

	if (enabled) {
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else {
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	resetCursorPos();
}

void CG::InputManager::toggleMouseCapture() noexcept
{
	setMouseCapture(!m_captureMouse);
	spdlog::info("mouse capture toggle");
}

void CG::InputManager::resetCursorPos() const noexcept
{
	int w, h;
	glfwGetWindowSize(m_window, &w, &h);
	glfwSetCursorPos(m_window, w * 0.5, h * 0.5);
}