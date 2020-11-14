#include <CG/components/Updateable.hpp>
#include "GameObjects/FreeCamera.hpp"

FreeCamera::FreeCamera()
{
	addComponent<CG::Updateable>([this](double d) { update(d); });
}

void FreeCamera::start()
{
	GameCamera->setPosition(glm::vec3(0, 0, 5));
	GameCamera->setFacingDirection(glm::vec3(-1, 0, 0));
	GameCamera->setUpDirection(glm::vec3(0, 1, 0));
	GameCamera->setFov(103);
	GameCamera->setAspectRatio(16 / 9);
	GameCamera->setRenderDistance(200);
}

void FreeCamera::update(double deltatime)
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


	if (InputManager->isKeyDown(GLFW_KEY_F1))
		InputManager->toggleMouseCapture();

	// Mouse
	auto mouseMove = InputManager->getMouseMovement();
	GameCamera->applyMouseMovement(
		static_cast<float>(mouseMove.x * m_rotSpeed * deltatime),
		static_cast<float>(mouseMove.y * m_rotSpeed * deltatime)
	);
}
