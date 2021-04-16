#pragma once

#include <array>

#include "CG/rendering/GLTriangles.hpp"
#include "CG/Color.hpp"

namespace CG {

class ShaderProgram;

class CubeRenderer {
public:
	CubeRenderer();

	void draw(const ShaderProgram &sm) const noexcept;

private:
	GLTriangles m_drawable;
};

}
