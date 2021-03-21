#include <CG/Game.hpp>

#include "CG/Material.hpp"
#include "GameObjects/Grid.hpp"
#include "GameObjects/Tile.hpp"


Grid::Grid(const CG::Vector2 &size, float height)
{
	for (int x = static_cast<int>(size.x * -.5); x < size.x * 0.5; ++x)
		for (int y = static_cast<int>(size.y * -.5); y < size.y * 0.5; ++y)
			CG::AGame::getGame()->instanciate<Tile>(
				CG::Vector3::Right() * x +
				CG::Vector3::Forward() * y +
				CG::Vector3::Up() * height,
				CG::Vector3::One(),
				(x + y) % 2 ? CG::Material::BlackRubber() : CG::Material::WhiteRubber());
}
