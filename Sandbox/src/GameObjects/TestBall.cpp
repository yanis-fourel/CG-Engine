#include <spdlog/spdlog.h>

#include <CG/components/renderer/ShapeRenderer.hpp>
#include <CG/components/OnUpdate.hpp>
#include <CG/components/Transform.hpp>
#include <CG/components/Rigidbody.hpp>
#include <CG/rendering/materials/MaterialTextured.hpp>
#include <CG/rendering/materials/MaterialSolid.hpp>
#include <CG/utils/Random.hpp>

#include "GameObjects/TestBall.hpp"
#include "AssetDir.hpp"

TestBall::TestBall(const CG::Vector3 &pos, float radius) : CG::prefabs::Sphere(pos, radius)
{
	setTag<"simulation_object"_hs>();

	auto mat = std::make_unique<CG::material::Textured>(ASSET_DIR "world-map.jpg");
	//auto mat = std::make_unique<CG::material::Solid>(CG::material::Solid::Gold());

	getComponent<CG::ShapeRenderer>().material = std::move(mat);
	//getComponent<CG::Transform>().rotation = CG::Quaternion::fromEuler(0.0, 0.0, 0.2);

	addComponent<CG::OnUpdate>([this](double d) {update(d); });

	auto &p = addComponent<CG::Rigidbody>();

	p.setVelocity(CG::Vector3::Zero());	
	p.setMass(1.0f);
	p.setDamping(0.95f);
	//p.setAcceleration(cyclone::Vector3::GRAVITY);

	p.setRestitution(0.759); // About a tennis ball
}

void TestBall::update(double deltatime)
{
	const auto rotVel = CG::Quaternion::fromEuler(1, 2, 3);
	getComponent<CG::Transform>().rotation *= rotVel * deltatime;
}
