#pragma once

#include <cyclone/body.h>

#include "CG/math/Vector3.hpp"
#include "CG/math/Quaternion.hpp"

#include "CG/GameObject.hpp"

namespace CG {

// TODO: hand craft all this for educational purposes

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
		m_body.setLinearDamping(1);
		m_body.setAngularDamping(1);
		m_body.setMass(1);
	}

public:
	void addForce(const CG::Vector3 &val) noexcept { m_body.addForce(val); }
	void addImpulse(const CG::Vector3 &val) noexcept { m_body.addVelocity(val); }
	void addRotationImpulse(const CG::Vector3 &val) noexcept { m_body.addRotation(val); }

	void addForceAtPoint(const CG::Vector3 &force, const CG::Vector3 &point) noexcept
	{
		updateBodyPositionRotation();

		m_body.addForceAtPoint(force, point);
	}

	// Rotation computation is far from being good
	void addImpulseAtPoint(const CG::Vector3 &impulse, const CG::Vector3 &point)
	{
		updateBodyPositionRotation();

		// This is a copy pasta of cyclone's `addForceAtPoint`, but we apply it as impulses instead of forces

		// Convert to coordinates relative to center of mass.
		Vector3 pt = point;
		pt -= m_body.getPosition();

		addImpulse(impulse);

		// Should take into account inertia ?
		addRotationImpulse(static_cast<cyclone::Vector3>(pt) % static_cast<cyclone::Vector3>(impulse));
	}

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


	void registerObject(GameObject &obj)
	{
		assert(m_gameObject == nullptr && "Don't call this method yourself. The engine will");
		m_gameObject = &obj;
	}

CG_INTERNAL_METHOD:
	void integrate(double deltatime) noexcept
	{
		updateBodyPositionRotation();

		m_body.integrate(deltatime);

		updateGameobjectTransform();
	}

private:
	void updateBodyPositionRotation()
	{
		const auto &t = m_gameObject->getComponent<CG::Transform>();

		m_body.setPosition(t.position);
		m_body.setOrientation(t.rotation);
	}

	void updateGameobjectTransform()
	{
		auto &t = m_gameObject->getComponent<CG::Transform>();

		t.position = m_body.getPosition();
		t.rotation = m_body.getOrientation();
	}

private:
	cyclone::RigidBody m_body;
	GameObject *m_gameObject = nullptr;

	double m_restitution = 1; // bouncyness
};

}
