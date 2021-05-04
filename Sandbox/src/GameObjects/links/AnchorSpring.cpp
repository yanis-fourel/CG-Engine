#include <spdlog/spdlog.h>

#include <CG/components/Updateable.hpp>
#include <CG/components/Transform.hpp>
#include <CG/components/Rigidbody.hpp>
#include <CG/components/renderer/LineRenderer.hpp>

#include "GameObjects/links/AnchorSpring.hpp"

AnchorSpring::AnchorSpring(const CG::Vector3 &anchor, CG::GameObject &b, double force, double restLength)
	: m_anchor(anchor), m_obj(b), m_force(force), m_restLength(restLength)
{
	addComponent<CG::LineRenderer>();
	addComponent<CG::Updateable>([this](double d) { update(d); });

	setTag<"simulation_object"_hs>();
}

void AnchorSpring::update(double d) noexcept
{
	auto pos1 = m_obj.getComponent<CG::Transform>().position;
	auto pos2 = m_anchor;

	auto currentLength = CG::Vector3::distance(pos1, pos2);

	auto force_1to2 = (pos2 - pos1).normalized() * m_force * (currentLength - m_restLength);

	auto &lr = getComponent<CG::LineRenderer>();
	lr.from = pos1;
	lr.to = pos2;

	lr.material.color = CG::Color::lerp(CG::Color::Green(), CG::Color::Red(), std::min(1.0, force_1to2.magnitude() * 0.2));

	if (getGame()->isFrozen())
		return;

	m_obj.getComponent<CG::Rigidbody>().addForce(force_1to2);
}
