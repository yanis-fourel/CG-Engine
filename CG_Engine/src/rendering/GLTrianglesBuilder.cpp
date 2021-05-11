#include "CG/rendering/GLTrianglesBuilder.hpp"
#include "CG/internal/GlError.hpp"

CG::GLTriangles CG::GLTrianglesBuilder::build() const noexcept
{
	CG::GLTriangles result;

	result.indices = indices;

	GLuint vbo;
	GLCall(glGenBuffers(1, &vbo));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type), vertices.data(), GL_STATIC_DRAW));

	GLCall(glGenVertexArrays(1, &result.vao));
	GLCall(glBindVertexArray(result.vao));
	GLCall(glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void *)offsetof(Vertex, position)));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void *)offsetof(Vertex, normal)));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(2,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void *)offsetof(Vertex, color)));
	GLCall(glEnableVertexAttribArray(2));
		GLCall(glVertexAttribPointer(3,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void *)offsetof(Vertex, textureUV)));
	GLCall(glEnableVertexAttribArray(3));

	return result;
}