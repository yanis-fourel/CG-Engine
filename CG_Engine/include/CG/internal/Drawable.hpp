#pragma once

#include <GL/glew.h>
#include <vector>

#include "ShaderProgram.hpp"

namespace CG {

struct Drawable {
	GLuint vao = -1;
	std::vector<unsigned int> indices;

	GLuint texture;
	bool hasTexture = false;

	inline void draw(const ShaderProgram &sm) const noexcept
	{
		glBindVertexArray(vao);

		// TODO: move texture handling in material
		sm.uploadUniform1b("u_hasTexture", hasTexture);
		if (hasTexture) // TODO: avoid branching here. Give texture to Material
			glBindTexture(GL_TEXTURE_2D, texture);

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
	}
};

}
