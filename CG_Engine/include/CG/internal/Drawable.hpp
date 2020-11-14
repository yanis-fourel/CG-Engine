#pragma once

#include <GL/glew.h>
#include <vector>

namespace CG {

struct Drawable {
	GLuint vbo = -1;
	GLuint vao = -1; // needed ?
	std::vector<unsigned int> indices;
	// Shader ref ? or in renderer

	inline void draw() const noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindVertexArray(vao); // needed ?

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
	}
};

}
