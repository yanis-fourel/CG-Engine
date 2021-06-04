#include "GameObjects/paddles/PlayerPaddle.hpp"

#include "LevelCreator.hpp"

PlayerPaddle::PlayerPaddle() : APaddle(Level::kDepth * 0.5, CG::Color::Blue(), CG::Color::White())
{
}

void PlayerPaddle::move(double deltatime)
{
	CG::Vector3 delta = CG::Vector3::Zero();

	if (InputManager->isKeyDown(GLFW_KEY_UP) /*|| InputManager->isKeyDown(GLFW_KEY_W) || InputManager->isKeyDown(GLFW_KEY_Z)*/)
		delta.y += 1;
	if (InputManager->isKeyDown(GLFW_KEY_DOWN) /*||InputManager->isKeyDown(GLFW_KEY_S)*/)
		delta.y -= 1;
	if (InputManager->isKeyDown(GLFW_KEY_LEFT) /*|| InputManager->isKeyDown(GLFW_KEY_A) || InputManager->isKeyDown(GLFW_KEY_Q) */)
		delta.x -= 1;
	if (InputManager->isKeyDown(GLFW_KEY_RIGHT) /*|| InputManager->isKeyDown(GLFW_KEY_D)*/)
		delta.x += 1;


	auto &pos = getComponent<CG::Transform>().position;

	pos += delta * kPaddleMaxSpeed * deltatime;


	{ // Clampf pos to stay inbounds
		auto size = getComponent<CG::Transform>().scale;

		auto maxPosX = 0.5 * (Level::kWidth - kPaddleWidth);
		auto maxPosY = 0.5 * (Level::kHeight - kPaddleHeight);

		pos.x = std::clamp<CG::Vector3::value_type>(pos.x, -maxPosX, maxPosX);
		pos.y = std::clamp<CG::Vector3::value_type>(pos.y, -maxPosY, maxPosY);
	}
}