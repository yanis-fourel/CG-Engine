#pragma once

#include "CG/Vector3.hpp"

namespace CG {

struct Transform 
{
	Vector3 position {0, 0, 0};
	// TODO: add rotation
	Vector3 scale {1, 1, 1};

	// TODO: should we cache model matrix here ? or in a dedicated component ?
};

}
