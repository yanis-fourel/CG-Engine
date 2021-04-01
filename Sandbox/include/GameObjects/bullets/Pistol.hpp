#pragma once

#include <CG/prefabs/Sphere.hpp>
#include <cyclone/particle.h>

class Pistol : public CG::prefabs::Sphere
{
public:
	Pistol(const CG::Vector3 &pos, float dampling);

private:
	void update(double deltatime);

private:
	cyclone::Particle m_particle;
};
