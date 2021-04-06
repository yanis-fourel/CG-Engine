#pragma once

#include "CG/math/Vector3.hpp"

namespace CG {

// All data are relative to the object's transform
struct SphereCollider
{
	Vector3 center = Vector3::Zero();
	float radius = 0.5f;
};

}
