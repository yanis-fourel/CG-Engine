#pragma once

#include <CG/prefabs/Sphere.hpp>
#include <cyclone/particle.h>

class Floating : public CG::prefabs::Sphere
{
public:
	Floating(const CG::Vector3 &pos, float dampling);

private:
	void update(double deltatime);

private:
	static constexpr float kFrequency = 1.f; // waves per second
	static constexpr float kAmplitude = 10.f;

	float m_lifetime = 0;
	cyclone::Particle m_particle;
};
