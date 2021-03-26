#pragma once

#include <CG/prefabs/Sphere.hpp>
#include <cyclone/particle.h>

class HomeworkBall : public CG::prefabs::Sphere
{
public:
	HomeworkBall(const CG::Vector3 &pos, float radius, float dampling);

private:
	void update(double deltatime);

private:
	cyclone::Particle m_particle;
};
