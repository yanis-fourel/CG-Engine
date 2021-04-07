#include <cyclone/particle.h>
#include <spdlog/spdlog.h>

#include <CG/components/Updateable.hpp>
#include <CG/components/Transform.hpp>

#include "GameObjects/Spring.hpp"

Spring::Spring(CG::AGameObject &a, CG::AGameObject &b, double force, double restLength)
	: m_obj1(a), m_obj2(b), m_force(force), m_restLength(restLength)
{
	// TODO: add Line renderer
	addComponent<CG::Updateable>([this](double d) { update(d); });

	setTag<"simulation_object"_hs>();
}

void Spring::update(double d) noexcept
{
	if (getGame()->isFrozen())
		return;

	auto pos1 = m_obj1.getComponent<CG::Transform>().position;
	auto pos2 = m_obj2.getComponent<CG::Transform>().position;

	auto currentLength = CG::Vector3::distance(pos1, pos2);

	auto force_1to2 = (pos2 - pos1).normalized() * m_force * (currentLength - m_restLength);

	//spdlog::info("Distance : {}, force : {} aka {}, {}, {}", currentLength, force_1to2.magnitude(), force_1to2.x, force_1to2.y, force_1to2.z);

	m_obj1.getComponent<cyclone::Particle>().addForce(force_1to2);
	m_obj2.getComponent<cyclone::Particle>().addForce(-force_1to2);
}
