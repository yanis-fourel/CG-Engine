#include "CG/components/renderer/PlaneRenderer.hpp"
#include "CG/internal/ColorVertex.hpp"

CG::PlaneRenderer::PlaneRenderer(const Color &colors)
{
#define P +0.5
#define N -0.5
	ColorVertex vertices[8]{
		{{N, 0, N}, colors},
		{{P, 0, N}, colors},
		{{P, 0, P}, colors},
		{{N, 0, P}, colors},
	};
#undef P
#undef N

	glGenBuffers(1, &m_drawable.vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_drawable.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_drawable.vao);
	glBindVertexArray(m_drawable.vao);
	glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(ColorVertex),
		(void *)offsetof(ColorVertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(ColorVertex),
		(void *)offsetof(ColorVertex, color));
	glEnableVertexAttribArray(1);


	m_drawable.indices = {
		0, 1, 2,
		0, 2, 3,
	};
}
