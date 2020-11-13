#pragma once

#include <glm/vec2.hpp>

namespace CG {

class InputManager
{
public:
	InputManager(GLFWwindow *window);

	// Don't call that yourself
	void update();

	[[nodiscard]] auto isKeyDown(int key) const noexcept -> bool;
	[[nodiscard]] auto getMouseMovement() const noexcept -> glm::vec2;

	void setMouseCapture(bool enabled) noexcept ;
	void toggleMouseCapture() noexcept;

private:
	bool m_captureMouse = true;
	glm::vec<2, double> m_mouseMovement{ 0, 0 };

	GLFWwindow *m_window;
};

}