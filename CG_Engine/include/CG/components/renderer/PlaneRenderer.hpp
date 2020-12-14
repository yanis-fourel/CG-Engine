#pragma once

#include "CG/internal/Drawable.hpp"
#include "CG/Color.hpp"

namespace CG {

class ShaderManager;

class PlaneRenderer {
public:
	// TODO: static shader

	PlaneRenderer(const Color &color);

	inline void draw(ShaderManager &) const noexcept { m_drawable.draw(); }
private:
	Drawable m_drawable;
};

}
