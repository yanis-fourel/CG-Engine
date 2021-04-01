#pragma once

#include <CG/prefabs/Sphere.hpp>
#include <cyclone/particle.h>

class Artillery : public CG::prefabs::Sphere
{
public:
	Artillery(const CG::Vector3 &pos, float dampling);

private:
	void update(double deltatime);

private:
	cyclone::Particle m_particle;
};
