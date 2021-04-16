#pragma once

#include "CG/GameObject.hpp"
#include "CG/math/Vector3.hpp"

namespace CG::prefabs {

class Sphere : public GameObject {
public:
	Sphere(const Vector3 &pos = CG::Vector3::Zero(), float radius = 0.5f);
};

}