#pragma once

#include <CG/prefabs/Plane.hpp>
#include <CG/math/Vector3.hpp>
#include <CG/components/material/MaterialSolid.hpp>

class Tile : public CG::prefabs::Plane
{
public:
	Tile(const CG::Vector3 &pos, const CG::Vector2 &scale, const CG::MaterialSolid &material);
};
