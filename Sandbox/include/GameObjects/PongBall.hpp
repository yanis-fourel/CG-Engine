#pragma once

#include <CG/prefabs/Sphere.hpp>
#include <CG/math/Vector3.hpp>

class PongBall : public CG::prefabs::Sphere
{
public:
	PongBall(const CG::Vector3 &pos, float radius = 0.5f);

private:
	void update(double deltatime) override;
	void onCollide(CG::GameObject &obj) override;

private:
	static constexpr double kBaseSpeed = 5.f;
	static constexpr double kAcceleration = 0.5f;
};
