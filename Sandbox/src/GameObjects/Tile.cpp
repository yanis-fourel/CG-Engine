#include <CG/components/Transform.hpp>
#include <CG/components/renderer/PlaneRenderer.hpp>

#include "GameObjects/Tile.hpp"

Tile::Tile(const CG::Vector3 &pos, const CG::Vector2 &scale, const CG::Material &material) 
	: CG::prefabs::Plane(pos, CG::Quaternion::fromEuler(0, 3.1415 * 0.5, 0), scale)
{
	getComponent<CG::PlaneRenderer>().setMaterial(material);
	setTag<"tile"_hs>();
}
