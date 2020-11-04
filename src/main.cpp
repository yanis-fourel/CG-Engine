/*
** EPITECH PROJECT, 2019
** openGl
** File description:
** main.cpp
*/

#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "AppWindow.hpp"
#include "ShaderManager.hpp"
#include "Camera.hpp"
#include "Utils.hpp"

struct Position
{
	static constexpr GLint kValueCount = 3;

	float x;
	float y;
	float z;
};

struct Color
{
	static constexpr GLint kValueCount = 4;

	float r;
	float g;
	float b;
	float a;
};

struct MyVertex
{
	Position pos;
	Color col;
};

int main()
{
	AppWindow window;

	MyVertex vertices[8]{
		// Position					Color
		{{-0.5f, -0.5f, -0.5f},   {1, 0, 0, 1}},
		{{0.5f,  -0.5f, -0.5f},   {0, 1, 0, 1}},
		{{ 0.5f,  0.5f, -0.5f},   {0, 0, 1, 1}},
		{{ -0.5f, 0.5f, -0.5f},   {0, 0, 0, 1}},

		{{-0.5f, -0.5f, 0.5f},    {1, 1, 0, 1}},
		{{0.5f,  -0.5f, 0.5f},    {0, 1, 1, 1}},
		{{ 0.5f,  0.5f, 0.5f},    {1, 0, 1, 1}},
		{{ -0.5f, 0.5f, 0.5f},    {1, 1, 1, 1}},

	};
	unsigned int indices[]{
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

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glVertexAttribPointer(0,
		Position::kValueCount,
		GL_FLOAT,
		GL_FALSE,
		sizeof(MyVertex),
		(void*)offsetof(MyVertex, pos));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,
		Color::kValueCount,
		GL_FLOAT,
		GL_FALSE,
		sizeof(MyVertex),
		(void*)offsetof(MyVertex, col));
	glEnableVertexAttribArray(1);

	ShaderManager sm;

	sm.addShader(GL_VERTEX_SHADER, "simple.vert");
	sm.addShader(GL_FRAGMENT_SHADER, "simple.frag");
	sm.validate();

	Camera cam;

	cam.setPosition(glm::vec3(0, 0, 5));
	cam.setFacingDirection(glm::vec3(0, 0, -1));
	cam.setUpDirection(glm::vec3(0, 1, 0));
	cam.setFov(103);
	cam.setAspectRatio(16 / 9);
	cam.setRenderDistance(20);


	auto camSpeed = 0.002f;
	auto rotSpeed = 0.001f;

	while (window.run()) {
		//
// INPUTS
//

// Keyboard
		if (window.isKeyDown(GLFW_KEY_W))
			cam.moveRelative(glm::vec3{ 0, 0, -1 } *camSpeed);
		if (window.isKeyDown(GLFW_KEY_S))
			cam.moveRelative(glm::vec3{ 0, 0, 1 }*camSpeed);
		if (window.isKeyDown(GLFW_KEY_A))
			cam.moveRelative(glm::vec3{ -1, 0, 0 }*camSpeed);
		if (window.isKeyDown(GLFW_KEY_D))
			cam.moveRelative(glm::vec3{ 1, 0, 0 }*camSpeed);
		if (window.isKeyDown(GLFW_KEY_Q))
			cam.moveRelative(glm::vec3{ 0, -1, 0 }*camSpeed);
		if (window.isKeyDown(GLFW_KEY_E))
			cam.moveRelative(glm::vec3{ 0, 1, 0 }*camSpeed);


		// Mouse
		auto mouseMove = window.getMouseMovemement();
		//cam.rotateEuler(glm::vec3(mouseMove.y* rotSpeed, mouseMove.x* rotSpeed, 0));
		cam.applyMouseMovement(mouseMove.x * rotSpeed, mouseMove.y * rotSpeed);

		glm::mat4 model = glm::mat4(1);
		sm.uploadUniformMat4("model", model);
		sm.uploadUniformMat4("viewProj", cam.getViewProjMatrix());
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(*indices), GL_UNSIGNED_INT, indices);
	}
}
