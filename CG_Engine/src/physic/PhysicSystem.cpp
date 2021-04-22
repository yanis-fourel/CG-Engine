
#include <spdlog/spdlog.h>

#include "CG/physic/PhysicSystem.hpp"
#include "CG/physic/collision/collisionDetector.hpp"

#include "CG/components/Rigidbody.hpp"
#include "CG/components/Transform.hpp"

#include "CG/components/collider/SphereCollider.hpp"

void CG::physic::update(const AGame &game, double deltatime) noexcept
{
	if (deltatime == 0) [[unlikely]]
		return;

	detail::integrateAll(game, deltatime);
	detail::resolveConstraints(game);
}

void CG::physic::detail::resolveConstraints(const AGame &game) noexcept
{
	constexpr int kIteration = 50;

	for (int i = 0; i < kIteration; i++)
		resolveConstraintsOnce(game);
}

void CG::physic::detail::resolveConstraintsOnce(const AGame &game) noexcept
{
	auto v = game.getWorld().view<Transform, Rigidbody, SphereCollider>();

	for (auto it = v.begin(); it != v.end(); ) {
		
		auto e1 = *it;

		it++;
		for (auto it2 = it; it2 != v.end(); it2++)
			handleCollision(game.getWorld(), e1, *it2);
	}
}

void CG::physic::detail::handleCollision(entt::registry &world, entt::entity e1, entt::entity e2) noexcept
{
	assert(e1 != e2);

	auto &t1 = world.get<Transform>(e1);
	auto &rb1 = world.get<Rigidbody>(e1);
	auto &col1 = world.get<SphereCollider>(e1);

	auto &t2 = world.get<Transform>(e2);
	auto &rb2 = world.get<Rigidbody>(e2);
	auto &col2 = world.get<SphereCollider>(e2);


	auto collision = checkCollision(t1, col1, t2, col2);

	if (!collision)
		return;

	auto imass1 = rb1.getInvertMass();
	auto imass2 = rb2.getInvertMass();

	auto totalInvertMass = imass1 + imass2;

	{ // position resolver

		auto movePerIMass = collision->hitNormal * (collision->penetration / totalInvertMass);

		t1.position += movePerIMass * imass1;
		t2.position -= movePerIMass * imass2;
	}

	{ // velocity resolver
		auto restitution = (rb1.getRestitution() + rb2.getRestitution()) / 2;

		auto separatingIndice = Vector3::dot(collision->hitNormal, rb1.getVelocity() - rb2.getVelocity());
		auto newSeparatingIndice = separatingIndice * -restitution;
		auto deltaSepIndice = newSeparatingIndice - separatingIndice;

		auto impulsePerIMass = collision->hitNormal * (deltaSepIndice / totalInvertMass);

		rb1.addImpulse(impulsePerIMass * imass1);
		rb2.addImpulse(-impulsePerIMass * imass2);
	}
}

void CG::physic::detail::integrateAll(const AGame &game, double deltatime) noexcept
{
	auto view = game.getWorld().view<Transform, Rigidbody>();

	view.each([&](Transform &transform, Rigidbody &rigidbody) {
		rigidbody.setPosition(transform.position);
		rigidbody.integrate(deltatime);

		transform.position = rigidbody.getPosition();
	});
}