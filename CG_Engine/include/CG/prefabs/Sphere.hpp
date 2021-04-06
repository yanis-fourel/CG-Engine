#pragma once

#include "CG/AGameObject.hpp"
#include "CG/math/Vector3.hpp"

namespace CG::prefabs {

class Sphere : public AGameObject {
public:
	Sphere(const Vector3 &pos = CG::Vector3::Zero(), float radius = 1.f);
};

}