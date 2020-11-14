#include <CG/components/Updateable.hpp>
#include "GameObjects/FreeCamera.hpp"

FreeCamera::FreeCamera()
{
	addComponent<CG::Updateable>([this](double d) { update(d); });
}

void FreeCamera::start()
{
	getGame()->getCamera().setPosition(glm::vec3(0, 0, 5));
	getGame()->getCamera().setFacingDirection(glm::vec3(0, 0, -1));
	getGame()->getCamera().setUpDirection(glm::vec3(0, 1, 0));
	getGame()->getCamera().setFov(103);
	getGame()->getCamera().setAspectRatio(16 / 9);
	getGame()->getCamera().setRenderDistance(200);
}

void FreeCamera::update(double deltatime)
{
	glm::vec3 move(0);

	if (getGame()->getInputManager().isKeyDown(GLFW_KEY_W))
		move.z -= 1;
	if (getGame()->getInputManager().isKeyDown(GLFW_KEY_S))
		move.z += 1;
	if (getGame()->getInputManager().isKeyDown(GLFW_KEY_A))
		move.x -= 1;
	if (getGame()->getInputManager().isKeyDown(GLFW_KEY_D))
		move.x += 1;
	if (getGame()->getInputManager().isKeyDown(GLFW_KEY_Q))
		move.y -= 1;
	if (getGame()->getInputManager().isKeyDown(GLFW_KEY_E))
		move.y += 1;

	getGame()->getCamera().moveRelative(move * static_cast<float>(m_speed * deltatime));


	if (getGame()->getInputManager().isKeyDown(GLFW_KEY_F1))
		getGame()->getInputManager().toggleMouseCapture();

	// Mouse
	auto mouseMove = getGame()->getInputManager().getMouseMovement();
	getGame()->getCamera().applyMouseMovement(
		static_cast<float>(mouseMove.x * m_rotSpeed * deltatime),
		static_cast<float>(mouseMove.y * m_rotSpeed * deltatime)
	);
}
