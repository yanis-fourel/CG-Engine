#include <numbers>

#include <spdlog/spdlog.h>

#include <CG/math/Vector3.hpp>
#include <CG/components/Transform.hpp>
#include <CG/components/Rigidbody.hpp>

#include "GameObjects/BuoyancyFApplier.hpp"

BuoyancyFApplier::BuoyancyFApplier(CG::GameObject &obj, float seaLevel, float seaDensity)
	: m_obj(obj), m_seaLevel(seaLevel), m_density(seaDensity)
{
	setTag<"simulation_object"_hs>();
}

void BuoyancyFApplier::update(double d)
{
	if (getGame()->isFrozen())
		return;

	const auto &trans = m_obj.getComponent<CG::Transform>();

	auto depth = m_seaLevel - trans.position.y - trans.scale.y * .5f;

	if (depth < 0)
		return;
	
	auto sphereVolume = (4.f/3.f) * std::numbers::pi * std::pow((trans.scale.x + trans.scale.y + trans.scale.z) / 3.0, 3);
	double verticalForce = std::min<CG::Vector3::value_type>(1, depth / trans.scale.y) * sphereVolume * m_density * 32.f;

	m_obj.getComponent<CG::Rigidbody>().addForce(CG::Vector3(0, verticalForce, 0));
}
