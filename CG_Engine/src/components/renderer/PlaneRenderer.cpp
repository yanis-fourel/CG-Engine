#include "CG/components/renderer/PlaneRenderer.hpp"
#include "CG/internal/Vertex.hpp"
#include "CG/internal/ShaderManager.hpp"


CG::PlaneRenderer::PlaneRenderer(const Color &color)
{
#define P +0.5
#define N -0.5
	Vertex vertices[8]{
		{{N, 0, N}, Vector3::Up(), color},
		{{P, 0, N}, Vector3::Up(), color},
		{{P, 0, P}, Vector3::Up(), color},
		{{N, 0, P}, Vector3::Up(), color},
	};
#undef P
#undef N

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_drawable.vao);
	glBindVertexArray(m_drawable.vao);
	glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void *)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void *)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void *)offsetof(Vertex, tint));
	glEnableVertexAttribArray(2);


	m_drawable.indices = {
		0, 1, 2,
		0, 2, 3,
	};
}

void CG::PlaneRenderer::draw(ShaderManager &sm) const noexcept
{
	m_drawable.draw(sm);
}
