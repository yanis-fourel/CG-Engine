#pragma once

#include "CG/math/Vector2.hpp"

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

	[[nodiscard]] auto getSize() const noexcept -> CG::Vector2;

	// Takes screen pixel position and return its normalized [-1, 1] position.
	[[nodiscard]] auto pointToNormalized(const Vector2 &pixelPos) const noexcept -> CG::Vector2;

private:
	void onFrameBegin();
	void onFrameEnd();

private:
	GLFWwindow *m_window;
	bool m_firstFrame = true;
};

}
