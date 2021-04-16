#pragma once

#include <CG/prefabs/Sphere.hpp>
#include <CG/math/Vector3.hpp>
#include <CG/rendering/materials/MaterialSolid.hpp>

#include <cyclone/particle.h>


class TestBall : public CG::prefabs::Sphere
{
public:
	TestBall(const CG::Vector3 &pos, float radius, const CG::material::Solid &material);

private:
	void update(double deltatime);
};
