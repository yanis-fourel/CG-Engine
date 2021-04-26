#pragma once

#include "CG/components/collider/PlaneCollider.hpp"
#include "CG/components/collider/SphereCollider.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/Rigidbody.hpp"

template <>
void CG::physic::localConstraintSolver(
	CG::Transform &t_plane, CG::Rigidbody &rb_plane, const CG::PlaneCollider &col_plane,
	CG::Transform &t_sphere, CG::Rigidbody &rb_sphere, const CG::SphereCollider &col_sphere)
{
	return;
}
