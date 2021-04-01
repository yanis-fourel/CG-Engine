#include <CG/Material.hpp>
#include <CG/components/renderer/SphereRenderer.hpp>
#include <CG/components/Updateable.hpp>
#include <CG/components/Transform.hpp>

#include <CG/InputManager.hpp>

#include "GameObjects/bullets/Fireball.hpp"

Fireball::Fireball(const CG::Vector3 &pos, float dampling) : CG::prefabs::Sphere(pos, 0.5f)
{
	getComponent<CG::SphereRenderer>().setMaterial(CG::Material::Ruby());

	addComponent<CG::Updateable>([this](double d) {update(d); });

	m_particle.setPosition(pos);
	m_particle.setVelocity(CG::Vector3::Forward() * 10.f);
	m_particle.setMass(1.f);
	m_particle.setDamping(dampling);
	m_particle.setAcceleration(CG::Vector3::Up() * 0.6f);
}

void Fireball::update(double deltatime)
{
	m_particle.integrate(deltatime);
	auto newpos = m_particle.getPosition();

	getComponent<CG::Transform>().position = newpos;

	if (newpos.magnitude() > 150)
		destroy();
}
