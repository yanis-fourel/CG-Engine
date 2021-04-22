#include <spdlog/spdlog.h>

#include <CG/components/Updateable.hpp>

#include "GameObjects/FreeCameraManager.hpp"

FreeCameraManager::FreeCameraManager()
{
	addComponent<CG::Updateable>([this](double d) { update(d); });
}

void FreeCameraManager::start()
{
	// arbitrary start position
	GameCamera->setPosition(glm::vec3(5, 58, 6));
	GameCamera->setFacingDirection(glm::vec3(-0.251, -0.737, -0.627));
	GameCamera->setUpDirection(glm::vec3(0, 1, 0));
	GameCamera->setFov(103);
	GameCamera->setAspectRatio(16.f / 9);
	GameCamera->setRenderDistance(99999);
	InputManager->setMouseCapture(false);
}

void FreeCameraManager::update(double deltatime)
{
	deltatime = getGame()->getRealDeltatime(); // camera should work even if game is paused

	glm::vec3 moveDirection(0);
	float verticalMove = 0;

	if (InputManager->isKeyDown(GLFW_KEY_W))
		moveDirection.z -= 1;
	if (InputManager->isKeyDown(GLFW_KEY_S))
		moveDirection.z += 1;
	if (InputManager->isKeyDown(GLFW_KEY_A))
		moveDirection.x -= 1;
	if (InputManager->isKeyDown(GLFW_KEY_D))
		moveDirection.x += 1;
	if (InputManager->isKeyDown(GLFW_KEY_Q))
		verticalMove -= 1;
	if (InputManager->isKeyDown(GLFW_KEY_E))
		verticalMove += 1;

	if (InputManager->isKeyDown(GLFW_KEY_LEFT_SHIFT) && glm::length(moveDirection) + std::abs(verticalMove) > 0)
		m_speedMul += deltatime * 10;
	else
		m_speedMul = 1;

	const float distanceMoved = static_cast<float>(m_speed * m_speedMul * deltatime);
	GameCamera->moveRelative(moveDirection * distanceMoved);
	GameCamera->moveAbs(CG::Vector3::Up() * verticalMove * distanceMoved);


	if (InputManager->isKeyPressed(GLFW_KEY_F1))
		InputManager->toggleMouseCapture();

	// Mouse
	auto mouseMove = InputManager->getMouseMovement();
	GameCamera->applyMouseMovement(
		static_cast<float>(mouseMove.x * m_rotSpeed),
		static_cast<float>(mouseMove.y * m_rotSpeed)
	);

}
