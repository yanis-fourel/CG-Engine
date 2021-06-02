#pragma once

#include "CG/math/Vector3.hpp"
#include "CG/Color.hpp"
#include "CG/rendering/materials/LineMaterial.hpp"	
#include "CG/GameObject.hpp"

namespace CG {

struct LineRenderer 
{
	CG::Vector3 from;
	CG::Vector3 to;

	CG::material::Line material;
	// TODO: width
};

}
