#include <CG/components/renderer/SphereRenderer.hpp>
#include <CG/components/Updateable.hpp>
#include <CG/components/Transform.hpp>

#include "GameObjects/TestBall.hpp"

TestBall::TestBall(const CG::Vector3 &pos, float radius, const CG::Material &material) : CG::prefabs::Sphere(pos, radius)
{
	getComponent<CG::SphereRenderer>().setMaterial(material);
	setTag<"simulation_object"_hs>();

	addComponent<CG::Updateable>([this](double d) {update(d); });

	auto &p = addComponent<cyclone::Particle>();

	p.setPosition(pos);
	p.setVelocity(CG::Vector3::Zero());
	p.setMass(1.0f);
	p.setDamping(0.95f);
	p.setAcceleration(cyclone::Vector3::GRAVITY);
}

void TestBall::update(double deltatime)
{
	if (deltatime == 0)
		return;

	auto &particle = getComponent<cyclone::Particle>();

	const auto radius = 0.5f;

	//particle.addForce(CG::Vector3(1.f, 0, 0));
	particle.setPosition(getComponent<CG::Transform>().position);


	particle.integrate(deltatime);

	auto pos = particle.getPosition();

	// Floor colision
	if (pos.y < radius) {
		pos.y = radius + (radius - pos.y);
		particle.setPosition(pos);

		auto vel = particle.getVelocity();
		vel.y = -vel.y;
		particle.setVelocity(vel);
	}

	// Invisible wall collision
	const auto wallX = 9.5;
	if (pos.x > wallX) {
		pos.x = wallX + (pos.x - wallX);
		particle.setPosition(pos);

		auto vel = particle.getVelocity();
		vel.x = -vel.x;
		particle.setVelocity(vel);
	}

	getComponent<CG::Transform>().position = pos;
}