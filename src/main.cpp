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
#include "Vertex.hpp"
#include "Cube.hpp"

int main()
{
	AppWindow window;

	Cube cube(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

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
		cam.applyMouseMovement(mouseMove.x * rotSpeed, mouseMove.y * rotSpeed);

		glm::mat4 model = glm::mat4(1);
		sm.uploadUniformMat4("model", model);
		sm.uploadUniformMat4("viewProj", cam.getViewProjMatrix());

		cube.draw();
	}
}
