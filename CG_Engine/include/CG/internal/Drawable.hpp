#pragma once

#include <GL/glew.h>
#include <vector>

#include "ShaderProgram.hpp"
#include "CG/Material.hpp"

namespace CG {

struct Drawable {
	GLuint vao = -1;
	std::vector<unsigned int> indices;

	// TODO: move material out of there, inside a component
	Material material = Material::Default();

	GLuint texture;
	bool hasTexture = false;

	// Shader ref ? or in renderer
	inline void draw(ShaderProgram &sm) const noexcept
	{
		glBindVertexArray(vao);

		sm.uploadUniformVec3("u_material.ambient", material.ambiant.toVec3());
		sm.uploadUniformVec3("u_material.diffuse", material.diffuse.toVec3());
		sm.uploadUniformVec3("u_material.specular", material.specular.toVec3());
		sm.uploadUniform1f("u_material.shininess", material.shininess);
		sm.uploadUniform1f("u_material.opacity", material.opacity);

		sm.uploadUniform1b("u_hasTexture", hasTexture);

		if (hasTexture) // TODO: avoid branching here. Give texture to Material
			glBindTexture(GL_TEXTURE_2D, texture);

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
	}
};

}
