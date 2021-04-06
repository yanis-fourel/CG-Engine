#pragma once

// TODO: abstract the keys, this is way too heavy to be included by every user's gameobject
#include <GL/glew.h> // needed by Glf3w
#include <GLFW/glfw3.h> // input keys

#include <CG/math/Vector2.hpp>

struct GLFWwindow;

namespace CG {

class InputManager
{
public:
	InputManager(GLFWwindow *window);

	// Don't call that yourself
	void update();

	// True while key is down
	[[nodiscard]] auto isKeyDown(int key) const noexcept -> bool;

	// True only the tick the key was pressed
	[[nodiscard]] auto isKeyPressed(int key) const noexcept -> bool;

	// True while key is up
	[[nodiscard]] auto isKeyUp(int key) const noexcept -> bool;

	// Only return a value if currently capturing mouse
	[[nodiscard]] auto getMouseMovement() const noexcept -> Vector2;

	// unit: Pixel. May be negative or bigger than window size if mouse is out of the window
	[[nodiscard]] auto getMousePosition() const noexcept -> Vector2;

	void setMouseCapture(bool enabled) noexcept;
	void toggleMouseCapture() noexcept;
	bool isMouseCaptured() const noexcept { return m_captureMouse; }
private:
	void resetCursorPos() const noexcept;

private:
	bool m_captureMouse{}; // only set via `setMouseCapture`
	Vector2 m_mouseMovement{ 0, 0 };

	GLFWwindow *m_window;
};

}