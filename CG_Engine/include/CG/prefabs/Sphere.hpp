#pragma once

#include "CG/GameObject.hpp"
#include "CG/Vector3.hpp"
#include "CG/Color.hpp"

namespace CG::prefabs {

class Sphere : public AGameObject {
public:
	Sphere(const Vector3 &pos, float radius);
};

}