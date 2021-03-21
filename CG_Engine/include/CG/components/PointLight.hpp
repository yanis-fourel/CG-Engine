#pragma once

#include "CG/Color.hpp"

namespace CG {

struct PointLight 
{
	Color color;

	float intensity = 1.f;

	float diffuseIntensity = 1.0f;
	float specularIntensity = 1.0f;

	// TODO: range or something
};

}
