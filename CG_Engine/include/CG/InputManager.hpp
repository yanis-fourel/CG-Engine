#pragma once

// TODO: abstract the keys, this is way too heavy to be included by every user's gameobject
#include <GL/glew.h> // needed by Glf3w
#include <GLFW/glfw3.h> // input keys

#include <CG/Vector2.hpp>

struct GLFWwindow;

namespace CG {

class InputManager
{
public:
	InputManager(GLFWwindow *window);

	// Don't call that yourself
	void update();

	[[nodiscard]] auto isKeyDown(int key) const noexcept -> bool;
	[[nodiscard]] auto getMouseMovement() const noexcept -> Vector2;

	void setMouseCapture(bool enabled) noexcept;
	void toggleMouseCapture() noexcept;

private:
	void resetCursorPos() const noexcept;

private:
	bool m_captureMouse{}; // only set via `setMouseCapture`
	Vector2 m_mouseMovement{ 0, 0 };

	GLFWwindow *m_window;
};

}