#include "Cube.hpp"
#include "Vertex.hpp"

Cube::Cube(glm::vec3 pos, glm::vec3 size)
{
	SimpleVertex vertices[8]{
		// Position																	Color
		{{pos.x + size.x * -0.5f, pos.y + size.y * -0.5f, pos.z + size.z * -0.5f},  {1, 0, 0, 1}},
		{{pos.x + size.x * 0.5f,  pos.y + size.y *-0.5f, pos.z + size.z * -0.5f},   {0, 1, 0, 1}},
		{{pos.x + size.x *  0.5f, pos.y + size.y * 0.5f, pos.z + size.z * -0.5f},   {0, 0, 1, 1}},
		{{pos.x + size.x *  -0.5f,pos.y + size.y * 0.5f, pos.z + size.z * -0.5f},   {0, 0, 0, 1}},

		{{pos.x + size.x * -0.5f, pos.y + size.y *-0.5f, pos.z + size.z * 0.5f},    {1, 1, 0, 1}},
		{{pos.x + size.x * 0.5f,  pos.y + size.y *-0.5f, pos.z + size.z * 0.5f},    {0, 1, 1, 1}},
		{{pos.x + size.x *  0.5f, pos.y + size.y * 0.5f, pos.z + size.z * 0.5f},    {1, 0, 1, 1}},
		{{pos.x + size.x *  -0.5f,pos.y + size.y * 0.5f, pos.z + size.z * 0.5f},    {1, 1, 1, 1}},
	};

	glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glVertexAttribPointer(0,
		Position::kValueCount,
		GL_FLOAT,
		GL_FALSE,
		sizeof(SimpleVertex),
		(void*)offsetof(SimpleVertex, pos));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,
		Color::kValueCount,
		GL_FLOAT,
		GL_FALSE,
		sizeof(SimpleVertex),
		(void*)offsetof(SimpleVertex, col));
	glEnableVertexAttribArray(1);
}

void Cube::draw()
{
	unsigned int kIndices[]{
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

	//TODO: which is needed ?
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBindVertexArray(_vao);

	glDrawElements(GL_TRIANGLES, sizeof(kIndices) / sizeof(*kIndices), GL_UNSIGNED_INT, kIndices);
}
