#include <CG/components/renderer/ShapeRenderer.hpp>
#include <CG/components/Transform.hpp>
#include <CG/rendering/materials/MaterialSolid.hpp>

#include "GameObjects/WaterCube.hpp"

WaterCube::WaterCube(const CG::Vector3 &pos, float sideSize) : CG::prefabs::Cube()
{
	setTag<"simulation_object"_hs>();

	{
		auto &t = addComponent<CG::Transform>();

		t.position = pos;
		t.position.y -= kHeight * 0.5;
		t.scale = CG::Vector3(sideSize, kHeight, sideSize);
	}

	auto material = CG::material::Solid{
		{0.f, 0.f, 1.f},
		{0.2f, 0.2f, 0.4f},
		{0.3f, 0.3f, 0.5f},
		32.f,
		0.5f
	};

	getComponent<CG::ShapeRenderer>().material = std::make_unique<CG::material::Solid>(material);
}
