#include <numbers>

#include <CG/rendering/materials/Checkerboard.hpp>
#include <CG/components/renderer/ShapeRenderer.hpp>
#include <CG/components/Rigidbody.hpp>

#include "GameObjects/Floor.hpp"

Floor::Floor(double height)
	: CG::prefabs::Plane(
		CG::Vector3(0, height, 0),
		CG::Quaternion::fromEuler(0, std::numbers::pi / 2, 0),
		CG::Vector2(999.0, 999.0)
	)
{
	auto material = std::make_unique<CG::material::Checkerboard>(CG::Color(0.2, 0.2, 0.2), CG::Color(0.6, 0.6, 0.6));

	material->ambiantFactor = 0.0; // Pitch black effect outside of range
	material->diffuseFactor = 0.5;
	material->specularFactor = 0.2;
	material->shininess = 8;

	getComponent<CG::ShapeRenderer>().material = std::move(material);
	addComponent<CG::Rigidbody>().setMass(std::numeric_limits<double>::infinity());

	setTag<"floor"_hs>();
}
