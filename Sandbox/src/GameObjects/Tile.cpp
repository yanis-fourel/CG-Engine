#include <CG/components/Transform.hpp>
#include <CG/components/renderer/PlaneRenderer.hpp>

#include "GameObjects/Tile.hpp"

Tile::Tile(const CG::Vector3 &pos, const CG::Vector3 &scale, const CG::Material &material)
{
	addComponent<CG::Transform>(pos, scale);
	addComponent<CG::PlaneRenderer>().setMaterial(material);
	setTag<"tile"_hs>();
}
