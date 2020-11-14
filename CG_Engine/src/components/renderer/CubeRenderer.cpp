#include "CG/components/renderer/CubeRenderer.hpp"
#include "CG/internal/ColorVertex.hpp"

CG::CubeRenderer::CubeRenderer(const std::array<Color, 8> &colors)
{
#define P +0.5
#define N -0.5
	ColorVertex vertices[8]{
		{{N, N, N}, colors[0]},
		{{P, N, N}, colors[1]},
		{{P, P, N}, colors[2]},
		{{N, P, N}, colors[3]},
		{{N, N, P}, colors[4]},
		{{P, N, P}, colors[5]},
		{{P, P, P}, colors[6]},
		{{N, P, P}, colors[7]},
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
		GL_DOUBLE,
		GL_FALSE,
		sizeof(ColorVertex),
		(void *)offsetof(ColorVertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,
		4,
		GL_DOUBLE,
		GL_FALSE,
		sizeof(ColorVertex),
		(void *)offsetof(ColorVertex, color));
	glEnableVertexAttribArray(1);


	m_drawable.indices = {
		// BOTTOM
		0, 1, 2,
		0, 2, 3,

		// FRONT
		0, 7, 3,
		0, 4, 7,

		// LEFT
		0, 1, 5,
		0, 5, 4,

		// BACK
		1, 2, 6,
		1, 6, 5,

		// RIGHT
		2, 3, 7,
		2, 7, 6,

		// UP
		4, 5, 6,
		4, 6, 7,
	};
}
