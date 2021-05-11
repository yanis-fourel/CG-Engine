#pragma once

#include <GL/glew.h>
#include <vector>

#include "CG/rendering/ShaderProgram.hpp"

namespace CG {

struct GLTriangles {
	GLuint vao;
	std::vector<unsigned int> indices; // note: very expensive copy 

	inline void draw(const ShaderProgram &sm) const noexcept
	{
		glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
	}
};

}
