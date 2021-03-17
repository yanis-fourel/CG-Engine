#pragma once

#include <CG/GameObject.hpp>

class Grid : public CG::AGameObject
{
public:
	explicit Grid(const CG::Vector2 &size, float height = 0);

private:
};
