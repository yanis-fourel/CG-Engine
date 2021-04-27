#include <CG/components/renderer/ShapeRenderer.hpp>
#include <CG/components/Updateable.hpp>
#include <CG/components/Transform.hpp>
#include <CG/components/Rigidbody.hpp>

#include "GameObjects/TestBall.hpp"

TestBall::TestBall(const CG::Vector3 &pos, float radius, const CG::material::Solid &material) : CG::prefabs::Sphere(pos, radius)
{
	setTag<"simulation_object"_hs>();

	getComponent<CG::ShapeRenderer>().material = std::make_unique<CG::material::Solid>(material);

	addComponent<CG::Updateable>([this](double d) {update(d); });

	auto &p = addComponent<CG::Rigidbody>();

	p.setVelocity(CG::Vector3::Zero());
	p.setMass(1.0f);
	p.setDamping(1.0f);
	p.setAcceleration(cyclone::Vector3::GRAVITY);

	p.setRestitution(0.759); // About a tennis ball
}

void TestBall::update(double deltatime)
{
	//if (deltatime == 0)
	//	return;

	//auto &rb = getComponent<CG::Rigidbody>();
	//auto &transform = getComponent<CG::Transform>();

	//const auto radius = transform.scale.y * 0.5;

	//auto pos = transform.position;

	//// Floor colision
	//if (pos.y < radius) {
	//	pos.y = radius + (radius - pos.y);
	//	transform.position = pos;

	//	auto vel = rb.getVelocity();
	//	vel.y = -vel.y;
	//	rb.setVelocity(vel);
	//}

	// Invisible wall collision
	//const auto wallX = 9.5;
	//if (pos.x > wallX) {
	//	pos.x = wallX + (pos.x - wallX);
	//	transform.position = pos

	//	auto vel = rb.getVelocity();
	//	vel.x = -vel.x;
	//	rb.setVelocity(vel);
	//}
}