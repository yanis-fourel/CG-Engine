#include "GameObjects/paddles/AIPaddle.hpp"

#include "LevelCreator.hpp"

AIPaddle::AIPaddle() : APaddle(Level::kDepth * -0.5, CG::Color::Red(), CG::Color::White())
{
	getObjectsOfTag<"ball"_hs>([&](CG::GameObject &obj) {
		m_ball = &obj;	
	});

	assert(m_ball && "Please instanciate ball *before* the paddle, or find a better way to get a reference to the ball");
}

void AIPaddle::move(double deltatime)
{
	// TODO: proper beatable AI
	auto &ballPos = m_ball->getComponent<CG::Transform>().position;
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
