#pragma once

#include "CG/GameObject.hpp"
#include "CG/components/Transform.hpp"

namespace CG::prefabs {

class Cube : public GameObject {
public:
	Cube(const CG::Transform &transform);
};

}