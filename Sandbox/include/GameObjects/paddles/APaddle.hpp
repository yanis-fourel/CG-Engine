#pragma once

#include <CG/GameObject.hpp>
#include <array>

#include "LevelCreator.hpp"

class APaddle : public CG::GameObject
{
protected:
	APaddle(float posZ, const CG::Color &color, const CG::Color &bordureColor);

protected:
	virtual void move(double deltatime) = 0;

private:
	void update(double deltatime) override;
	void lateUpdate(double deltatime) override;

	std::array<CG::GameObject *, 4> m_bordureRenderers;

protected:
	static constexpr double kPaddleWidth = Level::kWidth * 0.2;
	static constexpr double kPaddleHeight = kPaddleWidth;

	static constexpr double kPaddleMaxSpeed = 5; // unit / second

	static constexpr double kPaddleOpacity = 0.6;

};