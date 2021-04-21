#include "CG/Physic/PhysicSystem.hpp"

#include "CG/components/Rigidbody.hpp"
#include "CG/components/Transform.hpp"

void CG::physic::update(const AGame &game, double deltatime) noexcept
{
	if (deltatime == 0) [[unlikely]]
		return;

	auto view = game.getWorld().view<Transform, Rigidbody>();

	view.each([&](Transform &transform, Rigidbody &rigidbody) {
		rigidbody.setPosition(transform.position);
		rigidbody.integrate(deltatime);

		transform.position = rigidbody.getPosition();
	});
}
