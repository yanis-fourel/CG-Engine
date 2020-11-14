#pragma once

#include "CG/Vector2.hpp"

struct GLFWwindow;

namespace CG {

class Window
{
public:
	Window(const CG::Vector2 windowSize, const std::string &windowName);
	~Window();

	bool run();

	[[nodiscard]] auto getWindow() noexcept { return m_window; };
	void close() noexcept;

	auto getSize() const noexcept -> CG::Vector2;

private:
	void onFrameBegin();
	void onFrameEnd();

private:
	GLFWwindow *m_window;
	bool m_firstFrame = true;
};

}
