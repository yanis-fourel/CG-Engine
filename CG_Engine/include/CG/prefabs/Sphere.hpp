#pragma once

#include "CG/GameObject.hpp"
#include "CG/math/Vector3.hpp"

namespace CG::prefabs {

class Sphere : public AGameObject {
public:
	Sphere(const Vector3 &pos, float radius);
};

}