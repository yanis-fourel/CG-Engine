#include <numbers>

#include <spdlog/spdlog.h>
#include <cyclone/particle.h>

#include <CG/math/Vector3.hpp>
#include <CG/components/Updateable.hpp>
#include <CG/components/Transform.hpp>

#include "GameObjects/BuoyancyFApplier.hpp"

BuoyancyFApplier::BuoyancyFApplier(CG::GameObject &obj, float seaLevel, float seaDensity)
	: m_obj(obj), m_seaLevel(seaLevel), m_density(seaDensity)
{
	setTag<"simulation_object"_hs>();
	addComponent<CG::Updateable>([this](double d) {this->update(d); });
}

void BuoyancyFApplier::update(double d) noexcept
{
	if (getGame()->isFrozen())
		return;

	const auto &trans = m_obj.getComponent<CG::Transform>();
	auto &particle = m_obj.getComponent<cyclone::Particle>();

	auto depth = m_seaLevel - trans.position.y - trans.scale.y * .5f;

	if (depth < 0) {
		particle.setAcceleration(cyclone::Vector3::GRAVITY);
		return;
	}
	
	auto sphereVolume = (4.f/3.f) * std::numbers::pi * std::pow((trans.scale.x + trans.scale.y + trans.scale.z) / 3.0, 3);

	double verticalForce = std::min(1.f, depth / trans.scale.y) * sphereVolume * m_density * 32.f;


	spdlog::info("volume : {}\n\tdepth : {}\n\td : {}", sphereVolume, depth, depth / trans.scale.y);

	particle.addForce(CG::Vector3(0, verticalForce, 0));
}