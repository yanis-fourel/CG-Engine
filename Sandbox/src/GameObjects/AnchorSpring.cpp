#include <cyclone/particle.h>
#include <spdlog/spdlog.h>

#include <CG/components/Updateable.hpp>
#include <CG/components/Transform.hpp>

#include "GameObjects/AnchorSpring.hpp"

AnchorSpring::AnchorSpring(const CG::Vector3 &anchor, CG::AGameObject &b, double force, double restLength)
	: m_anchor(anchor), m_obj(b), m_force(force), m_restLength(restLength)
{
	// TODO: add Line renderer
	addComponent<CG::Updateable>([this](double d) { update(d); });

	setTag<"simulation_object"_hs>();
}

void AnchorSpring::update(double d) noexcept
{
	if (getGame()->isFrozen())
		return;

	auto pos1 = m_obj.getComponent<CG::Transform>().position;
	auto pos2 = m_anchor;

	auto currentLength = CG::Vector3::distance(pos1, pos2);

	auto force_1to2 = (pos2 - pos1).normalized() * m_force * (currentLength - m_restLength);

	m_obj.getComponent<cyclone::Particle>().addForce(force_1to2);
}
