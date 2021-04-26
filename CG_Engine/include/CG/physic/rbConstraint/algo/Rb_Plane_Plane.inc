#pragma once

#include "CG/components/collider/PlaneCollider.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/Rigidbody.hpp"


// Planes are currently infinite, solving them shouldn't make sense (easy to bet UB if we get 3 planes)

template <>
void CG::physic::localConstraintSolver(
	CG::Transform &t1, CG::Rigidbody &rb1, const CG::PlaneCollider &col1,
	CG::Transform &t2, CG::Rigidbody &rb2, const CG::PlaneCollider &col2)
{
	return;
}
