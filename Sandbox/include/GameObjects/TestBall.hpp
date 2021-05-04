#pragma once

#include <CG/prefabs/Sphere.hpp>
#include <CG/math/Vector3.hpp>
#include <CG/rendering/materials/MaterialSolid.hpp>

class TestBall : public CG::prefabs::Sphere
{
public:
	TestBall(const CG::Vector3 &pos, float radius = 0.5f, const CG::material::Solid &material = CG::material::Solid::Default());

private:
	void update(double deltatime);
};
