#pragma once

#include <CG/prefabs/Sphere.hpp>
#include <CG/math/Vector3.hpp>
#include <CG/components/material/MaterialSolid.hpp>

#include <cyclone/particle.h>


class TestBall : public CG::prefabs::Sphere
{
public:
	TestBall(const CG::Vector3 &pos, float radius, const CG::MaterialSolid &material);

private:
	void update(double deltatime);
};
