#include "GameObjects/paddles/AIPaddle.hpp"

#include "LevelCreator.hpp"

AIPaddle::AIPaddle() : APaddle(Level::kDepth * -0.5, CG::Color::Red(), CG::Color::White())
{}

void AIPaddle::move(double deltatime)
{
	// TODO: proper beatable AI
	auto &ballPos = getBall().getComponent<CG::Transform>().position;
	auto &pos = getComponent<CG::Transform>().position;

	pos.x = ballPos.x;
	pos.y = ballPos.y;


	{ // Clampf pos to stay inbounds
		auto size = getComponent<CG::Transform>().scale;

		auto maxPosX = 0.5 * (Level::kWidth - kPaddleWidth);
		auto maxPosY = 0.5 * (Level::kHeight - kPaddleHeight);

		pos.x = std::clamp<CG::Vector3::value_type>(pos.x, -maxPosX, maxPosX);
		pos.y = std::clamp<CG::Vector3::value_type>(pos.y, -maxPosY, maxPosY);
	}
}
