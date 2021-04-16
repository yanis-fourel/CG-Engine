#pragma once

#include <CG/prefabs/Plane.hpp>
#include <CG/math/Vector3.hpp>
#include <CG/rendering/materials/MaterialSolid.hpp>

class Tile : public CG::prefabs::Plane
{
public:
	Tile(const CG::Vector3 &pos, const CG::Vector2 &scale, const CG::material::Solid &material);
};
