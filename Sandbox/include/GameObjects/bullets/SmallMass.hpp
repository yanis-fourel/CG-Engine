#pragma once

#include <CG/prefabs/Sphere.hpp>
#include <cyclone/particle.h>

class SmallMass : public CG::prefabs::Sphere
{
public:
	SmallMass(const CG::Vector3 &pos, float dampling);

private:
	void update(double deltatime);

private:
	cyclone::Particle m_particle;
};
