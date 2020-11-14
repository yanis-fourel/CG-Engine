#pragma once

#include <GL/glew.h>
#include <vector>

namespace CG {

struct Drawable {
	GLuint vao = -1;
	std::vector<unsigned int> indices;
	// Shader ref ? or in renderer

	inline void draw() const noexcept
	{
		glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
	}
};

}
