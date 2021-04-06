#pragma once

#include "CG/AGameObject.hpp"
#include "CG/math/Vector3.hpp"
#include "CG/Color.hpp"

namespace CG::prefabs {

class PointLight : public AGameObject {
public:
	PointLight(const Vector3 &pos, const Color &color);

};

}