#pragma once

#include <array>

#include "CG/internal/Drawable.hpp"
#include "CG/Color.hpp"

namespace CG {

class ShaderProgram;

class CubeRenderer {
public:
	CubeRenderer();

	void draw(ShaderProgram &sm) const noexcept;

private:
	Drawable m_drawable;
};

}
