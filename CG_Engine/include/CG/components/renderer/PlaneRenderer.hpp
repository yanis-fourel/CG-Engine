#pragma once

#include "CG/Material.hpp"
#include "CG/internal/Drawable.hpp"
#include "CG/Color.hpp"

namespace CG {

class ShaderManager;

class PlaneRenderer {
public:
	// TODO: static shader

	PlaneRenderer();

	void draw(ShaderManager &sm) const noexcept;

	[[nodiscard]] auto getMaterial() const noexcept -> const Material &{ return m_drawable.material; }
	void setMaterial(const Material &mat) noexcept { m_drawable.material = mat; }

private:
	Drawable m_drawable;
};

}
