#include "CG/rendering/materials/MaterialSolid.hpp"

void CG::material::Solid::uploadUniforms() const noexcept
{
	const auto &shader = getMaterialShader<Solid>();

	shader.uploadUniformVec3("u_material.ambient", ambiant.toVec3());
	shader.uploadUniformVec3("u_material.diffuse", diffuse.toVec3());
	shader.uploadUniformVec3("u_material.specular", specular.toVec3());
	shader.uploadUniform1f("u_material.shininess", shininess);
	shader.uploadUniform1f("u_material.opacity", opacity);
}
