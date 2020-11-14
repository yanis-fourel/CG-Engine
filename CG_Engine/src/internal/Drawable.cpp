#include "CG/internal/Drawable.hpp"

void CG::Drawable::draw() const noexcept
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao); // needed ?

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, indices.data());
}
