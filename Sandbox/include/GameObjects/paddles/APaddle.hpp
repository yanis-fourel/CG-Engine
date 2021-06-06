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
	CG::GameObject &getBall() const { return *m_ball; }

private:
	void update(double deltatime) override;
	void lateUpdate(double deltatime) override;
	bool doesCollideWithBall(const CG::Transform &ballTransform) const noexcept;

private:
	std::array<CG::GameObject *, 4> m_bordureRenderers;
	CG::GameObject *m_ball = nullptr;

protected:
	static constexpr double kPaddleWidth = Level::kWidth * 0.2;
	static constexpr double kPaddleHeight = kPaddleWidth;

	static constexpr double kPaddleMaxSpeed = 5; // unit / second

	static constexpr double kPaddleOpacity = 0.6;

};