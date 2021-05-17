#pragma once

#include <cyclone/body.h>

#include "CG/math/Vector3.hpp"
#include "CG/math/Quaternion.hpp"

namespace CG {

// TODO: hand made Rigidbody that could directly use the Transform (more sexy and probably more performant)

// note: only supports SphereCollider for now
class Rigidbody 
{
public:
	static constexpr CG::Vector3 kGravity = {
		static_cast<CG::Vector3::value_type>(0), 
		static_cast<CG::Vector3::value_type>(-9.81),
		static_cast<CG::Vector3::value_type>(0)
	};

	public:
		Rigidbody()
		{
			m_body.setAwake(true);
		}
public:
	void addForce(const CG::Vector3 &val) noexcept { m_body.addForce(val); }
	void addImpulse(const CG::Vector3 &val) noexcept;

	void setVelocity(const CG::Vector3 &val) noexcept { m_body.setVelocity(val); }
	void setAcceleration(const CG::Vector3 &val) noexcept { m_body.setAcceleration(val); }

	void setAngularVelocity(const CG::Vector3 &val) noexcept { m_body.setRotation(val); }

	void setMass(double val) noexcept { m_body.setMass(val); }
	void setLinearDamping(double val) noexcept { m_body.setLinearDamping(val); }
	void setAngularDamping(double val) noexcept { m_body.setAngularDamping(val); }
	void setRestitution(double val) noexcept { m_restitution = val; }


	[[nodiscard]] auto getVelocity() const noexcept -> CG::Vector3 { return m_body.getVelocity(); }
	[[nodiscard]] auto getAcceleration() const noexcept -> CG::Vector3 { return m_body.getAcceleration(); }

	[[nodiscard]] auto getAngularVelocity() const noexcept -> CG::Vector3 { return m_body.getRotation(); }


	[[nodiscard]] auto getMass() const noexcept -> double { return m_body.getMass(); }
	[[nodiscard]] auto getInvertMass() const noexcept -> double { return m_body.getInverseMass(); }
	[[nodiscard]] auto getLinearDamping() const noexcept -> double { return m_body.getLinearDamping(); }
	[[nodiscard]] auto getAngularDamping() const noexcept -> double { return m_body.getAngularDamping(); }
	[[nodiscard]] auto getRestitution() const noexcept -> double { return m_restitution; }

CG_INTERNAL_METHOD:
	void setPosition(const CG::Vector3 &val) noexcept { m_body.setPosition(val); }
	void setRotation(const CG::Quaternion &val) noexcept { m_body.setOrientation(val); }

	[[nodiscard]] auto getPosition() const noexcept -> CG::Vector3 { return m_body.getPosition(); }
	[[nodiscard]] auto getRotation() const noexcept -> CG::Quaternion { return m_body.getOrientation(); }

	void integrate(double deltatime) noexcept { m_body.integrate(deltatime); }

private:
	cyclone::RigidBody m_body;
	
	double m_restitution = 1;
};

}
