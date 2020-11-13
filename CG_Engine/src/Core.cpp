#include "CG/Core.hpp"
#include "CG/Camera.hpp"
#include "CG/Window.hpp"
#include "CG/ShaderManager.hpp"

#include "CG/internal/Shaders.hpp"

CG::Core::Core(std::unique_ptr<AGame> game) : m_game(std::move(game))
{}

int CG::Core::run()
{
	Window window;


	ShaderManager sm;

	sm.addShader(GL_VERTEX_SHADER, CG::shaders::simple_vert);
	sm.addShader(GL_FRAGMENT_SHADER, CG::shaders::simple_frag);
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
		m_game->update(0);

		// TODO: Move into game

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

		if (window.isKeyDown(GLFW_KEY_F1))
			window.toggleMouseCapture();

		// Mouse
		auto mouseMove = window.getMouseMovemement();
		cam.applyMouseMovement(mouseMove.x * rotSpeed, mouseMove.y * rotSpeed);

		glm::mat4 model = glm::mat4(1);
		sm.uploadUniformMat4("model", model);
		sm.uploadUniformMat4("viewProj", cam.getViewProjMatrix());

		sm.use();
	}

	return 0;
}
