#include "CG/components/renderer/CubeRenderer.hpp"
#include "CG/internal/Vertex.hpp"

CG::CubeRenderer::CubeRenderer(const Color &color)
{
	Vertex vertices[24]{
		//bottom
		{(Vector3::Down() + Vector3::Left() + Vector3::Backward()) * 0.5,	Vector3::Down(), color},
		{(Vector3::Down() + Vector3::Left() + Vector3::Forward()) * 0.5,	Vector3::Down(), color},
		{(Vector3::Down() + Vector3::Right() + Vector3::Forward()) * 0.5,	Vector3::Down(), color},
		{(Vector3::Down() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Down(), color},

		//front
		{(Vector3::Down() + Vector3::Left() + Vector3::Backward()) * 0.5,	Vector3::Backward(), color},
		{(Vector3::Up() + Vector3::Left() + Vector3::Backward()) * 0.5,		Vector3::Backward(), color},
		{(Vector3::Up() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Backward(), color},
		{(Vector3::Down() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Backward(), color},

		//left
		{(Vector3::Down() + Vector3::Left() + Vector3::Backward()) * 0.5,	Vector3::Right(), color},
		{(Vector3::Down() + Vector3::Left() + Vector3::Forward()) * 0.5,	Vector3::Right(), color},
		{(Vector3::Up() + Vector3::Left() + Vector3::Forward()) * 0.5,		Vector3::Right(), color},
		{(Vector3::Up() + Vector3::Left() + Vector3::Backward()) * 0.5,		Vector3::Right(), color},

		//back
		{(Vector3::Down() + Vector3::Left() + Vector3::Forward()) * 0.5,	Vector3::Forward(), color},
		{(Vector3::Down() + Vector3::Right() + Vector3::Forward()) * 0.5,	Vector3::Forward(), color},
		{(Vector3::Up() + Vector3::Right() + Vector3::Forward()) * 0.5,		Vector3::Forward(), color},
		{(Vector3::Up() + Vector3::Left() + Vector3::Forward()) * 0.5,		Vector3::Forward(), color},

		//right
		{(Vector3::Down() + Vector3::Right() + Vector3::Forward()) * 0.5,	Vector3::Left(), color},
		{(Vector3::Down() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Left(), color},
		{(Vector3::Up() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Left(), color},
		{(Vector3::Up() + Vector3::Right() + Vector3::Forward()) * 0.5,		Vector3::Left(), color},

		//up
		{(Vector3::Up() + Vector3::Left() + Vector3::Backward()) * 0.5,		Vector3::Up(), color},
		{(Vector3::Up() + Vector3::Left() + Vector3::Forward()) * 0.5,		Vector3::Up(), color},
		{(Vector3::Up() + Vector3::Right() + Vector3::Forward()) * 0.5,		Vector3::Up(), color},
		{(Vector3::Up() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Up(), color},
	};

	m_drawable.indices = {
		//bottom
		0, 1, 2,
		0, 2, 3,

		//front
		4, 5, 6,
		4, 6, 7,

		//left
		8, 9, 10,
		8, 10, 11,

		//back
		12, 13, 14,
		12, 14, 15,

		//right
		16, 17, 18,
		16, 18, 19,

		// top
		20, 21, 22,
		20, 22, 23
	};

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
}
