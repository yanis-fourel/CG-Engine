#pragma once

#include "CG/math/Vector3.hpp"

namespace CG {

// All data are relative to the object's transform
struct PlaneCollider
{
	Vector3 normal = Vector3::Forward();
	Vector3 point = Vector3::Zero();
};

}
