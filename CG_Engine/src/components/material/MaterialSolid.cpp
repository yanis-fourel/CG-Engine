#include "CG/components/material/MaterialSolid.hpp"

void CG::MaterialSolid::uploadUniforms() const noexcept
{
	const auto &shader = getMaterialShader<MaterialSolid>();

	shader.uploadUniformVec3("u_material.ambient", ambiant.toVec3());
	shader.uploadUniformVec3("u_material.diffuse", diffuse.toVec3());
	shader.uploadUniformVec3("u_material.specular", specular.toVec3());
	shader.uploadUniform1f("u_material.shininess", shininess);
	shader.uploadUniform1f("u_material.opacity", opacity);
}
