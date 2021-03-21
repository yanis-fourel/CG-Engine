#pragma once

#include "CG/math/Vector3.hpp"
#include "CG/math/Quaternion.hpp"

namespace CG {

struct Transform 
{
	Vector3 position {0, 0, 0};
	Quaternion rotation = Quaternion::identity();
	Vector3 scale {1, 1, 1};

	// TODO: should we cache model matrix here for optimisation ? or in a dedicated component ?
};

}
