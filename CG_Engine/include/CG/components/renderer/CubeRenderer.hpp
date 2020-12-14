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

	void draw(ShaderManager &sm) const noexcept;
private:
	Drawable m_drawable;
};

}
