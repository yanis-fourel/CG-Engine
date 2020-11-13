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

	[[nodiscard]] auto getWindow() noexcept { return m_window; };
	void close() noexcept;
private:
	void onFrameBegin();
	void onFrameEnd();

private:
	GLFWwindow *m_window;
	bool m_firstFrame = true;
};

}
