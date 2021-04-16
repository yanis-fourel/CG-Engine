#include <CG/components/renderer/ShapeRenderer.hpp>
#include <CG/components/Updateable.hpp>
#include <CG/components/Transform.hpp>

#include "GameObjects/TestBall.hpp"

TestBall::TestBall(const CG::Vector3 &pos, float radius, const CG::material::Solid &material) : CG::prefabs::Sphere(pos, radius)
{
	setTag<"simulation_object"_hs>();

	getComponent<CG::ShapeRenderer>().material = std::make_unique<CG::material::Solid>(material);

	addComponent<CG::Updateable>([this](double d) {update(d); });

	auto &p = addComponent<cyclone::Particle>();

	p.setPosition(pos);
	p.setVelocity(CG::Vector3::Zero());
	p.setMass(1.0f);
	p.setDamping(0.8f);
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
	//const auto wallX = 9.5;
	//if (pos.x > wallX) {
	//	pos.x = wallX + (pos.x - wallX);
	//	particle.setPosition(pos);

	//	auto vel = particle.getVelocity();
	//	vel.x = -vel.x;
	//	particle.setVelocity(vel);
	//}

	getComponent<CG::Transform>().position = pos;
}