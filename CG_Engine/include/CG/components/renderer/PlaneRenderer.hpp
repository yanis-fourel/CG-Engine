#pragma once

#include "CG/internal/Drawable.hpp"
#include "CG/Color.hpp"

namespace CG {

class ShaderProgram;

class PlaneRenderer {
public:
	PlaneRenderer();

	void draw(const ShaderProgram &sm) const noexcept;

private:
	Drawable m_drawable;
};

}
