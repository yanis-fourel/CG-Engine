#pragma once

#include "CG/Color.hpp"

namespace CG {

struct PointLight 
{
	Color color;

	float intensity;

	float diffuseIntensity = 0.5f;
	float specularIntensity = 1.0f;

	// TODO: range or something
};

}
