#include <CG/components/Transform.hpp>
#include <CG/components/renderer/CubeRenderer.hpp>
#include <CG/components/material/MaterialSolid.hpp>

#include "GameObjects/WaterCube.hpp"

WaterCube::WaterCube(const CG::Vector3 &pos, float sideSize) : CG::prefabs::Cube(CG::Transform{ pos, CG::Quaternion::identity(), CG::Vector3(sideSize, kHeight, sideSize) })
{
	getComponent<CG::Transform>().position.y -= kHeight * 0.5;

	auto material = CG::MaterialSolid{
		.ambiant = {0.f, 0.f, 1.f},
		.diffuse = {0.2f, 0.2f, 0.4f},
		.specular = {0.3f, 0.3f, 0.5f},
		.shininess = 32.f,
		.opacity = 0.5f
	};

	addComponent<CG::MaterialSolid>(material);
}
