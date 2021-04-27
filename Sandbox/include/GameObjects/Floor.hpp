#pragma once

#include <CG/prefabs/Plane.hpp>

class Floor : public CG::prefabs::Plane
{
public:
	explicit Floor(double height);
};
