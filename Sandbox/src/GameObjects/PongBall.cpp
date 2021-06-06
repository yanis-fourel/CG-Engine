#include <spdlog/spdlog.h>

#include <CG/components/renderer/ShapeRenderer.hpp>
#include <CG/components/Rigidbody.hpp>
#include <CG/rendering/materials/MaterialTextured.hpp>
#include <CG/rendering/materials/MaterialSolid.hpp>
#include <CG/utils/Random.hpp>

#include "GameObjects/PongBall.hpp"
#include "AssetDir.hpp"

PongBall::PongBall(const CG::Vector3 &pos, float radius) : CG::prefabs::Sphere(pos, radius)
{
	setTag<"ball"_hs>();

	auto mat = std::make_unique<CG::material::Textured>(ASSET_DIR "world-map.jpg");
	//auto mat = std::make_unique<CG::material::Solid>(CG::material::Solid::Gold());

	getComponent<CG::ShapeRenderer>().material = std::move(mat);
	//getComponent<CG::Transform>().rotation = CG::Quaternion::fromEuler(0.0, 0.0, 0.2);

	auto &p = addComponent<CG::Rigidbody>();

	p.setVelocity(CG::Vector3::Zero());
	p.setMass(1.0f);
	p.setLinearDamping(1.f);
	p.setAngularDamping(1.f);
	//p.setAcceleration(cyclone::Vector3::GRAVITY);
	//p.setAngularVelocity(CG::Vector3(1, 2, 3));

	p.setRestitution(1.f);


	auto initialDirection = CG::Vector3::Forward() * CG::Quaternion::fromEuler(
		CG::random::range(-std::numbers::pi / 4, std::numbers::pi / 4),
		CG::random::range(-std::numbers::pi / 4, std::numbers::pi / 4),
		0
	);

	if (CG::random::oneIn(2))
		initialDirection.z = -initialDirection.z;

	p.setVelocity(initialDirection * kBaseSpeed);
}

void PongBall::update(double deltatime)
{
	//const auto rotVel = CG::Quaternion::fromEuler(1, 2, 3);
	//getComponent<CG::Transform>().rotation *= rotVel * deltatime;

	auto &rb = getComponent<CG::Rigidbody>();

	rb.setVelocity(rb.getVelocity() + rb.getVelocity().normalized() * kAcceleration * deltatime);
}

void PongBall::onCollide(CG::GameObject &obj)
{

}
