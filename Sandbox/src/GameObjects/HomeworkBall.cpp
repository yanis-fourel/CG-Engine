#include <CG/Material.hpp>
#include <CG/components/renderer/SphereRenderer.hpp>
#include <CG/components/Updateable.hpp>
#include <CG/components/Transform.hpp>

#include <CG/InputManager.hpp>

#include "GameObjects/HomeworkBall.hpp"

HomeworkBall::HomeworkBall(const CG::Vector3 &pos, float radius, float dampling) : CG::prefabs::Sphere(pos, radius)
{
	getComponent<CG::SphereRenderer>().setMaterial(CG::Material::Ruby());

	addComponent<CG::Updateable>([this](double d) {update(d); });

	m_particle.setPosition(pos);
	m_particle.setVelocity(CG::Vector3::Zero());
	m_particle.setMass(1.0f);
	m_particle.setDamping(dampling);
	m_particle.setAcceleration(cyclone::Vector3::GRAVITY);

}

void HomeworkBall::update(double deltatime)
{
	const auto radius = getComponent<CG::Transform>().scale.y;

	m_particle.addForce(CG::Vector3(1.f, 0, 0));

	m_particle.integrate(deltatime);
	
	auto pos = m_particle.getPosition();

	// Floor colision
	if (pos.y < radius) {
		pos.y = radius + (radius - pos.y);
		m_particle.setPosition(pos);

		auto vel = m_particle.getVelocity();
		vel.y = -vel.y;
		m_particle.setVelocity(vel);
	}

	// Invisible wall collision
	const auto wallX = 9.5;
	if (pos.x > wallX) {
		pos.x = wallX + (pos.x - wallX);
		m_particle.setPosition(pos);

		auto vel = m_particle.getVelocity();
		vel.x = -vel.x;
		m_particle.setVelocity(vel);
	}

	getComponent<CG::Transform>().position = pos;
}
