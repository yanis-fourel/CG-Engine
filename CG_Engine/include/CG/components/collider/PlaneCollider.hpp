#pragma once

#include "CG/math/Vector3.hpp"
#include "CG/GameObject.hpp"

namespace CG {

// All data are relative to the object's transform
struct PlaneCollider
{
	Vector3 normal = Vector3::Up();
	Vector3 point = Vector3::Zero();
};

}
