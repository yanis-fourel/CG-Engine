#include "BridgeFactory.hpp"
#include "GameObjects/TestBall.hpp"
#include "GameObjects/links/Spring.hpp"
#include "GameObjects/links/AnchorSpring.hpp"
#include "GameObjects/links/Rod.hpp"
#include "GameObjects/links/AnchorCable.hpp"


void createBridge(CG::AGame &game)
{
	constexpr auto kStart = CG::Vector3(0, 5, 0);
	constexpr auto kEnd = CG::Vector3(0, 5, 10);
	constexpr auto kWidth = 2.f;
	constexpr auto kStepCount = 5u;
	constexpr auto kCablesHeight = 3.f;

	std::vector<CG::GameObject *> leftBalls;
	std::vector<CG::GameObject *> rightBalls;

	// Balls
	{
		const auto ballSideOffset = CG::Vector3::cross(kEnd - kStart, CG::Vector3::Up()).normalized() * (kWidth / 2);

		for (auto step = 0u; step < kStepCount; step++)
		{
			auto centerPos = CG::Vector3::lerp(kStart, kEnd, static_cast<double>(step) / kStepCount);

			leftBalls.push_back(&game.instanciate<TestBall>(centerPos + ballSideOffset));
			rightBalls.push_back(&game.instanciate<TestBall>(centerPos - ballSideOffset));
		}
	}


	// Springs between balls
	{
		const auto ballForwadDistance = CG::Vector3::distance(kStart, kEnd) / (kStepCount);

		for (auto step = 0u; step < kStepCount; step++) {
			

			if (step > 0) {
				game.instanciate<Rod>(*leftBalls[step - 1], *leftBalls[step], ballForwadDistance);
				game.instanciate<Rod>(*rightBalls[step - 1], *rightBalls[step], ballForwadDistance);
			}

			game.instanciate<Rod>(*leftBalls[step], *rightBalls[step], kWidth);
		}
	}


	// Anchored springs above balls
	{
		for (auto step = 0u; step < kStepCount; step++) {
			auto leftPos = leftBalls[step]->getComponent<CG::Transform>().position;
			auto rightPos = rightBalls[step]->getComponent<CG::Transform>().position;

			game.instanciate<AnchorCable>(leftPos + CG::Vector3::Up() * kCablesHeight, *leftBalls[step], kCablesHeight);
			game.instanciate<AnchorCable>(rightPos + CG::Vector3::Up() * kCablesHeight, *rightBalls[step], kCablesHeight);
		}
	}
}
