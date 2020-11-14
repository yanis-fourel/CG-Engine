#include <spdlog/spdlog.h>

#include <CG/components/Updateable.hpp>

#include "GameObjects/FreeCameraManager.hpp"

FreeCameraManager::FreeCameraManager()
{
	addComponent<CG::Updateable>([this](double d) { update(d); });
}

void FreeCameraManager::start()
{
	GameCamera->setPosition(glm::vec3(0, 5, 0));
	GameCamera->setFacingDirection(glm::vec3(0.5, -0.707, 0.5));
	GameCamera->setUpDirection(glm::vec3(0, 1, 0));
	GameCamera->setFov(103);
	GameCamera->setAspectRatio(16 / 9);
	GameCamera->setRenderDistance(200);
	InputManager->setMouseCapture(false);
}

void FreeCameraManager::update(double deltatime)
{
	glm::vec3 move(0);

	if (InputManager->isKeyDown(GLFW_KEY_W))
		move.z -= 1;
	if (InputManager->isKeyDown(GLFW_KEY_S))
		move.z += 1;
	if (InputManager->isKeyDown(GLFW_KEY_A))
		move.x -= 1;
	if (InputManager->isKeyDown(GLFW_KEY_D))
		move.x += 1;
	if (InputManager->isKeyDown(GLFW_KEY_Q))
		move.y -= 1;
	if (InputManager->isKeyDown(GLFW_KEY_E))
		move.y += 1;

	GameCamera->moveRelative(move * static_cast<float>(m_speed * deltatime));


	if (InputManager->isKeyPressed(GLFW_KEY_F1))
		InputManager->toggleMouseCapture();

	// Mouse
	auto mouseMove = InputManager->getMouseMovement();
	GameCamera->applyMouseMovement(
		static_cast<float>(mouseMove.x * m_rotSpeed),
		static_cast<float>(mouseMove.y * m_rotSpeed)
	);
}
