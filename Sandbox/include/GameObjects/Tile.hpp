#pragma once

#include <CG/AGameObject.hpp>
#include <CG/math/Vector3.hpp>
#include <CG/Material.hpp>

class Tile : public CG::AGameObject
{
public:
	Tile(const CG::Vector3 &pos, const CG::Vector3 &scale, const CG::Material &material);
};
