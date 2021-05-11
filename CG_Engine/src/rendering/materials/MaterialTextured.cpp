#include "CG/rendering/materials/MaterialTextured.hpp"
#include "CG/rendering/Texture.hpp"
#include "CG/internal/GlError.hpp"

void CG::material::Textured::uploadUniforms() const noexcept
{
	const auto &shader = getShader();

	shader.uploadUniformVec3("u_material.ambient", ambiant.toVec3());
	shader.uploadUniformVec3("u_material.diffuse", diffuse.toVec3());
	shader.uploadUniformVec3("u_material.specular", specular.toVec3());
	shader.uploadUniform1f("u_material.shininess", shininess);
	shader.uploadUniform1f("u_material.opacity", opacity);

	glBindTexture(GL_TEXTURE_2D, textureID);
}

// TODO: proper assets cache
void CG::material::Textured::setTexture(std::string_view path)
{
	auto t = Texture(path.data());

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t.width, t.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, t.data);

	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
