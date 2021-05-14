#pragma once

#include <CG/prefabs/Sphere.hpp>
#include <CG/math/Vector3.hpp>

class TestBall : public CG::prefabs::Sphere
{
public:
	TestBall(const CG::Vector3 &pos, float radius = 0.5f);

private:
	void update(double deltatime);
	void onCollide(CG::GameObject &obj);
};
