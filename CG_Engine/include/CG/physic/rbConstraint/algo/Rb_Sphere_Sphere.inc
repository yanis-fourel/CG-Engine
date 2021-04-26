#pragma once

#include "CG/physic/collision/collisionDetector.hpp"

#include "CG/components/collider/SphereCollider.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/Rigidbody.hpp"

template <>
void CG::physic::localConstraintSolver(
	CG::Transform &t1, CG::Rigidbody &rb1, const CG::SphereCollider &col1,
	CG::Transform &t2, CG::Rigidbody &rb2, const CG::SphereCollider &col2)
{
	auto collision = checkCollision(t1, col1, t2, col2);

	if (!collision)
		return;

	auto imass1 = rb1.getInvertMass();
	auto imass2 = rb2.getInvertMass();

	auto totalInvertMass = imass1 + imass2;

	{ // position resolver

		auto movePerIMass = collision->hitNormal * (collision->penetration / totalInvertMass);

		t1.position += movePerIMass * imass1;
		t2.position -= movePerIMass * imass2;
	}

	{ // velocity resolver

		auto restitution = (rb1.getRestitution() + rb2.getRestitution()) / 2;

		auto separatingIndice = Vector3::dot(collision->hitNormal, rb1.getVelocity() - rb2.getVelocity());
		auto newSeparatingIndice = separatingIndice * -restitution;
		auto deltaSepIndice = newSeparatingIndice - separatingIndice;

		auto impulsePerIMass = collision->hitNormal * (deltaSepIndice / totalInvertMass);

		rb1.addImpulse(impulsePerIMass * imass1);
		rb2.addImpulse(-impulsePerIMass * imass2);
	}
}
