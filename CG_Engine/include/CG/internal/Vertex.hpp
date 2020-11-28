#pragma once

#include "CG/Vector3.hpp"
#include "CG/Color.hpp"

namespace CG
{

struct Vertex
{
	Vector3 position;
	Vector3 normal;

	Color color;
};

}
