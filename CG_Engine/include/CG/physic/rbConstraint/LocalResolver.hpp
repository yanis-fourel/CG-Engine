#pragma once

//
// A local resolver solves constaints between TWO object having Transform, Rigidbody and Collider
//


#include "CG/components/Rigidbody.hpp"

#include "CG/physic/collision/collisionDetector.hpp"

namespace CG::physic {

// Returns whether or not object did collide
template <typename Col1, typename Col2>
bool localConstraintSolver(
	CG::Transform &t1, CG::Rigidbody &rb1, const Col1 &col1,
	CG::Transform &t2, CG::Rigidbody &rb2, const Col2 &col2)
{
	auto collision = checkCollision(t1, col1, t2, col2);

	if (!collision)
		return false;

	auto imass1 = rb1.getInvertMass();
	auto imass2 = rb2.getInvertMass();

	auto totalInvertMass = imass1 + imass2;

	{ // derivative resolver
		auto restitution = (rb1.getRestitution() + rb2.getRestitution()) / 2;

		// TODO: take into account both object's velocity `at impact point`, which can change depending on current roation velocity
		auto separatingIndice = Vector3::dot(collision->hitNormal, rb1.getVelocity() - rb2.getVelocity());
		auto newSeparatingIndice = separatingIndice * -restitution;
		auto deltaSepIndice = newSeparatingIndice - separatingIndice;

		auto impulsePerIMass = collision->hitNormal * (deltaSepIndice / totalInvertMass);

		// TODO: take into account frictions
		rb1.addImpulseAtPoint(impulsePerIMass * imass1, collision->hitPosition);
		rb2.addImpulseAtPoint(-impulsePerIMass * imass2, collision->hitPosition);
	}

	{ // position resolver

		auto movePerIMass = collision->hitNormal * (collision->penetration / totalInvertMass);

		t1.position += movePerIMass * imass1;
		t2.position -= movePerIMass * imass2;
	}

	return true;
}

}
