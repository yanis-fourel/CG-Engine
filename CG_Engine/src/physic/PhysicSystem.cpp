
#include <spdlog/spdlog.h>
#include <entt/entt.hpp>

#include "CG/physic/PhysicSystem.hpp"
#include "CG/physic/rbConstraint/GlobalResolverSystem.hpp"

#include "CG/components/Rigidbody.hpp"
#include "CG/components/Transform.hpp"

#include "CG/components/collider/SphereCollider.hpp"
#include "CG/components/collider/PlaneCollider.hpp"

#include "CG/components/CustomPhysicResolver.hpp"


void CG::physic::update(const AGame &game, double deltatime) noexcept
{
	if (deltatime != 0) [[likely]]
		detail::integrateAll(game, deltatime);
	detail::resolveConstraints(game);
}

void CG::physic::detail::integrateAll(const AGame &game, double deltatime) noexcept
{
	auto view = game.getWorld().view<Transform, Rigidbody>();

	view.each([&](Transform &transform, Rigidbody &rigidbody) {
		rigidbody.integrate(deltatime);
		});
}


void CG::physic::detail::resolveConstraints(const AGame &game) noexcept
{
	constexpr int kIteration = 50;

	CG::physic::globalConstraintSolver<true, SphereCollider, PlaneCollider>(game.getWorld());

	for (int i = 0; i < kIteration - 1; i++) {
		game.getWorld().view<CG::CustomPhysicResolver>().each([](const CG::CustomPhysicResolver &resolver) {
			resolver.call();
			});

		CG::physic::globalConstraintSolver<false, SphereCollider, PlaneCollider>(game.getWorld());
	}
}
