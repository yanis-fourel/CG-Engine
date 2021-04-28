#pragma once

#include "CG/GameObject.hpp"
#include "CG/math/Vector3.hpp"
#include "CG/math/Vector2.hpp"
#include "CG/math/Quaternion.hpp"
#include "CG/components/Transform.hpp"

namespace CG::prefabs {

class Plane : public GameObject {
public:
	explicit Plane(const CG::Transform &transform);
	Plane(const Vector3 &pos, const Quaternion &normalRotation, const Vector2 &size);
};

}
