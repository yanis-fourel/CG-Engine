#include "CG/rendering/materials/Checkerboard.hpp"

void CG::material::Checkerboard::uploadUniforms() const noexcept
{
	const auto &shader = getShader();

	shader.uploadUniformVec3("u_color1", color1.toVec3());
	shader.uploadUniformVec3("u_color2", color2.toVec3());
	shader.uploadUniformVec3("u_size", size);
	shader.uploadUniform1f("u_shininess", shininess);
	shader.uploadUniform1f("u_ambiantFact", ambiantFactor);
	shader.uploadUniform1f("u_diffuseFact", diffuseFactor);
	shader.uploadUniform1f("u_specularFact", specularFactor);
}
