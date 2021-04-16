#pragma once

#include "CG/rendering/GLTriangles.hpp"
#include "CG/Color.hpp"

namespace CG {

class ShaderProgram;

class PlaneRenderer {
public:
	PlaneRenderer();

	void draw(const ShaderProgram &sm) const noexcept;

private:
	GLTriangles m_drawable;
};

}
