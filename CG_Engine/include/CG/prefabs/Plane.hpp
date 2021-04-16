#pragma once

#include "CG/GameObject.hpp"
#include "CG/math/Vector3.hpp"
#include "CG/math/Vector2.hpp"
#include "CG/math/Quaternion.hpp"

namespace CG::prefabs {

class Plane : public GameObject {
public:
	Plane(const Vector3 &pos, const Quaternion &normalRotation, const Vector2 &size);
};

}
