#include "CG/rendering/materials/LineMaterial.hpp"

void CG::material::Line::uploadUniforms() const noexcept
{
	getShader().uploadUniformVec3("u_color", color.toVec3());
}
