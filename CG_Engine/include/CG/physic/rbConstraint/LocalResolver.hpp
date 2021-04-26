#pragma once

//
// A local resolver solves constaints between TWO object having Transform, Rigidbody and Collider
//


#include "CG/components/Transform.hpp"
#include "CG/components/Rigidbody.hpp"

namespace CG::physic {

// Each collider type pair has a specific implementation
template <typename Col1, typename Col2>
void localConstraintSolver(
	CG::Transform &t1, CG::Rigidbody &rb1, const Col1 &col1,
	CG::Transform &t2, CG::Rigidbody &rb2, const Col2 &col2)
{
	localConstraintSolver(t2, rb2, col2, t1, rb1, col1);
}

}

#include "algo/_all.inc"
