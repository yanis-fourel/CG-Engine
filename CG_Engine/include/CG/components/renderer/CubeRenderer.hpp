#pragma once

#include <array>

#include "CG/internal/Drawable.hpp"
#include "CG/Color.hpp"

namespace CG {

class ShaderManager;

class CubeRenderer {
public:
	// TODO: static shader

	CubeRenderer(const Color &colors);

	inline void draw(ShaderManager &) const noexcept { m_drawable.draw(); }
private:
	Drawable m_drawable;
};

}
