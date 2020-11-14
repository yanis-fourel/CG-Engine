#pragma once

#include <CG/GameObject.hpp>
#include <CG/Vector3.hpp>
#include <CG/Color.hpp>

class Tile : public CG::AGameObject
{
public:
	Tile(const CG::Vector3 &pos, const CG::Vector3 &scale, const CG::Color &color);
};
