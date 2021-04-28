#include <CG/components/renderer/ShapeRenderer.hpp>
#include <CG/components/Updateable.hpp>
#include <CG/components/Transform.hpp>
#include <CG/components/Rigidbody.hpp>

#include "GameObjects/TestBall.hpp"

TestBall::TestBall(const CG::Vector3 &pos, float radius, const CG::material::Solid &material) : CG::prefabs::Sphere(pos, radius)
{
	setTag<"simulation_object"_hs>();

	getComponent<CG::ShapeRenderer>().material = std::make_unique<CG::material::Solid>(material);
	//getComponent<CG::Transform>().rotation = CG::Quaternion::fromEuler(0.0, 0.0, 0.2);

	//addComponent<CG::Updateable>([this](double d) {update(d); });

	auto &p = addComponent<CG::Rigidbody>();

	p.setVelocity(CG::Vector3::Zero());
	p.setMass(1.0f);
	p.setDamping(1.0f);
	p.setAcceleration(cyclone::Vector3::GRAVITY);

	p.setRestitution(0.759); // About a tennis ball
}

void TestBall::update(double deltatime)
{
	// uncomment the a addComponent<CG::Updateable>() to use that
}