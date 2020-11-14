#pragma once

#include <array>

#include "CG/internal/Drawable.hpp"
#include "CG/Color.hpp"

namespace CG {

class CubeRenderer {
public:
	// TODO: static shader

	CubeRenderer(const std::array<Color, 8> &colors);

	inline void draw() const noexcept { m_drawable.draw(); }
private:
	Drawable m_drawable;
};

}
