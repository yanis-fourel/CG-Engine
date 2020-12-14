#pragma once

#include <GL/glew.h>
#include <vector>

#include "ShaderManager.hpp"

namespace CG {

struct Drawable {
	GLuint vao = -1;
	std::vector<unsigned int> indices;

	GLuint texture;
	bool hasTexture = false;

	// Shader ref ? or in renderer

	inline void draw(ShaderManager &sm) const noexcept
	{
		glBindVertexArray(vao);

		sm.uploadUniform1b("u_hasTexture", hasTexture);

		if (hasTexture) 
			glBindTexture(GL_TEXTURE_2D, texture);

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
	}
};

}
