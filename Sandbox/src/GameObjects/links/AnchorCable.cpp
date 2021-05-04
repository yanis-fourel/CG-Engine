#include <CG/components/Updateable.hpp>
#include <CG/components/Rigidbody.hpp>
#include <CG/components/renderer/LineRenderer.hpp>

#include "GameObjects/links/AnchorCable.hpp"

AnchorCable::AnchorCable(const CG::Vector3 &anchor, CG::GameObject &b, double length) : m_anchor(anchor), m_obj(b), m_length(length)
{
	setTag<"simulation_object"_hs>();

	addComponent<CG::Updateable>([this](double d) {update(d); });
	addComponent<CG::LineRenderer>().material.color = CG::Color::Grey();
}


void AnchorCable::update(double) noexcept
{
	auto p = m_obj.getComponent<CG::Transform>().position;

	auto distance = CG::Vector3::distance(p, m_anchor);

	auto dir = (m_anchor - p).normalized();
	auto move = dir * (distance - m_length);

	if (!getGame()->isFrozen() && distance > m_length) {
		m_obj.getComponent<CG::Transform>().position += move;

		auto vel = m_obj.getComponent<CG::Rigidbody>().getVelocity();
		auto dot = CG::Vector3::dot(dir, vel);
		if (dot < 0) {
			vel -= dir * dot;
			m_obj.getComponent<CG::Rigidbody>().setVelocity(vel);
		}
	}

	auto &lr = getComponent<CG::LineRenderer>();
	lr.from = m_anchor;
	lr.to = m_obj.getComponent<CG::Transform>().position;
	lr.material.color = CG::Color::lerp(CG::Color::Grey(), CG::Color::Magenta(), std::min(1.0, distance / m_length - 1));
}
