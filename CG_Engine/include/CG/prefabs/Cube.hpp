#pragma once

#include "CG/AGameObject.hpp"
#include "CG/components/Transform.hpp"

namespace CG::prefabs {

class Cube : public AGameObject {
public:
	Cube(const CG::Transform &transform);
};

}