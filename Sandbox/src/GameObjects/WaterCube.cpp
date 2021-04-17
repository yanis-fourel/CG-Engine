#include <CG/components/Transform.hpp>
#include <CG/components/renderer/ShapeRenderer.hpp>
#include <CG/rendering/materials/MaterialSolid.hpp>

#include "GameObjects/WaterCube.hpp"

WaterCube::WaterCube(const CG::Vector3 &pos, float sideSize) : CG::prefabs::Cube(CG::Transform{ pos, CG::Quaternion::identity(), CG::Vector3(sideSize, kHeight, sideSize) })
{
	setTag<"simulation_object"_hs>();
	getComponent<CG::Transform>().position.y -= kHeight * 0.5;

	auto material = CG::material::Solid{
		{0.f, 0.f, 1.f},
		{0.2f, 0.2f, 0.4f},
		{0.3f, 0.3f, 0.5f},
		32.f,
		0.5f
	};

	getComponent<CG::ShapeRenderer>().material = std::make_unique<CG::material::Solid>(material);
}
