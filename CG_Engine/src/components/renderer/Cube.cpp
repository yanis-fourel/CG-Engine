#include "CG/components/renderer/ShapeRenderer.hpp"
#include "CG/rendering/ShaderProgram.hpp"
#include "CG/rendering/GLTrianglesBuilder.hpp"

CG::ShapeRenderer CG::ShapeRenderer::Cube()
{
	GLTrianglesBuilder builder;

	builder.vertices = {
		//bottom
		{(Vector3::Down() + Vector3::Left() + Vector3::Backward()) * 0.5,	Vector3::Down(), Color::White()},
		{(Vector3::Down() + Vector3::Left() + Vector3::Forward()) * 0.5,	Vector3::Down(), Color::White()},
		{(Vector3::Down() + Vector3::Right() + Vector3::Forward()) * 0.5,	Vector3::Down(), Color::White()},
		{(Vector3::Down() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Down(), Color::White()},

		//front
		{(Vector3::Down() + Vector3::Left() + Vector3::Backward()) * 0.5,	Vector3::Backward(), Color::White()},
		{(Vector3::Up() + Vector3::Left() + Vector3::Backward()) * 0.5,		Vector3::Backward(), Color::White()},
		{(Vector3::Up() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Backward(), Color::White()},
		{(Vector3::Down() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Backward(), Color::White()},

		//left
		{(Vector3::Down() + Vector3::Left() + Vector3::Backward()) * 0.5,	Vector3::Right(), Color::White()},
		{(Vector3::Down() + Vector3::Left() + Vector3::Forward()) * 0.5,	Vector3::Right(), Color::White()},
		{(Vector3::Up() + Vector3::Left() + Vector3::Forward()) * 0.5,		Vector3::Right(), Color::White()},
		{(Vector3::Up() + Vector3::Left() + Vector3::Backward()) * 0.5,		Vector3::Right(), Color::White()},

		//back
		{(Vector3::Down() + Vector3::Left() + Vector3::Forward()) * 0.5,	Vector3::Forward(), Color::White()},
		{(Vector3::Down() + Vector3::Right() + Vector3::Forward()) * 0.5,	Vector3::Forward(), Color::White()},
		{(Vector3::Up() + Vector3::Right() + Vector3::Forward()) * 0.5,		Vector3::Forward(), Color::White()},
		{(Vector3::Up() + Vector3::Left() + Vector3::Forward()) * 0.5,		Vector3::Forward(), Color::White()},

		//right
		{(Vector3::Down() + Vector3::Right() + Vector3::Forward()) * 0.5,	Vector3::Left(), Color::White()},
		{(Vector3::Down() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Left(), Color::White()},
		{(Vector3::Up() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Left(), Color::White()},
		{(Vector3::Up() + Vector3::Right() + Vector3::Forward()) * 0.5,		Vector3::Left(), Color::White()},

		//up
		{(Vector3::Up() + Vector3::Left() + Vector3::Backward()) * 0.5,		Vector3::Up(), Color::White()},
		{(Vector3::Up() + Vector3::Left() + Vector3::Forward()) * 0.5,		Vector3::Up(), Color::White()},
		{(Vector3::Up() + Vector3::Right() + Vector3::Forward()) * 0.5,		Vector3::Up(), Color::White()},
		{(Vector3::Up() + Vector3::Right() + Vector3::Backward()) * 0.5,	Vector3::Up(), Color::White()},
	};

	builder.indices = {
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
	
	return CG::ShapeRenderer(std::move(builder.build()));

	/*GLuint vbo;
	GLCall(glGenBuffers(1, &vbo));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

	GLCall(glGenVertexArrays(1, &m_drawable.vao));
	GLCall(glBindVertexArray(m_drawable.vao));
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
	GLCall(glEnableVertexAttribArray(2));*/
}
