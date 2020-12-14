#pragma once

#include "CG/internal/Drawable.hpp"
#include "CG/Color.hpp"

namespace CG {

class ShaderManager;

class PlaneRenderer {
public:
	// TODO: static shader

	PlaneRenderer(const Color &color);

	void draw(ShaderManager &sm) const noexcept;
private:
	Drawable m_drawable;
};

}
