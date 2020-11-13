#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace CG {

class Window
{
public:
	Window();
	~Window();

	bool run();

	bool isKeyDown(int key);
	glm::vec2 getMouseMovemement();

	void setMouseCapture(bool enabled) { m_captureMouse = enabled; }
	void toggleMouseCapture() { m_captureMouse = !m_captureMouse; }
private:
	void onFrameBegin();
	void onFrameEnd();

	void processInputs();

private:
	bool m_captureMouse = true;

	GLFWwindow* m_window;
	bool m_firstFrame = true;

	glm::vec<2, double> m_mouseMovement{ 0, 0 };
};

}
