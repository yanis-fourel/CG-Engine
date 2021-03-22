#pragma once

#include <CG/prefabs/Sphere.hpp>

class TestBall : public CG::prefabs::Sphere
{
public:
	TestBall(const CG::Vector3 &pos, float radius);

private:
	void update(double deltatime);
};
