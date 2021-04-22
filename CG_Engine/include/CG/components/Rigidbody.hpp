#pragma once

#include <cyclone/particle.h>

#include "CG/math/Vector3.hpp"

namespace CG {

// TODO: hand made Rigidbody that could directly use the Transform (more sexy and probably more performant)

// note: only supports SphereCollider for now
class Rigidbody 
{
public:
	static constexpr CG::Vector3 kGravity = {0, -9.81, 0};

public:
	void addForce(const CG::Vector3 &val) noexcept { m_particle.addForce(val); }
	void addImpulse(const CG::Vector3 &val) noexcept;

	void setVelocity(const CG::Vector3 &val) noexcept { m_particle.setVelocity(val); }
	void setAcceleration(const CG::Vector3 &val) noexcept { m_particle.setAcceleration(val); }

	void setMass(double val) noexcept { m_particle.setMass(val); }
	void setDamping(double val) noexcept { m_particle.setDamping(val); }
	void setRestitution(double val) noexcept { m_restitution = val; }


	[[nodiscard]] auto getVelocity() const noexcept -> CG::Vector3 { return m_particle.getVelocity(); }
	[[nodiscard]] auto getAcceleration() const noexcept -> CG::Vector3 { return m_particle.getAcceleration(); }

	[[nodiscard]] auto getMass() const noexcept -> double { return m_particle.getMass(); }
	[[nodiscard]] auto getInvertMass() const noexcept -> double { return m_particle.getInverseMass(); }
	[[nodiscard]] auto getDamping() const noexcept -> double { return m_particle.getDamping(); }
	[[nodiscard]] auto getRestitution() const noexcept -> double { return m_restitution; }

CG_INTERNAL_METHOD:
	void setPosition(const CG::Vector3 &val) noexcept { m_particle.setPosition(val); }

	[[nodiscard]] auto getPosition() const noexcept -> CG::Vector3 { return m_particle.getPosition(); }

	void integrate(double deltatime) noexcept { m_particle.integrate(deltatime); }

private:
	cyclone::Particle m_particle;
	
	double m_restitution = 1;
};

}
