#include "CG/physic/Raycast.hpp"
#include "CG/AGameobject.hpp"

auto CG::castRaycast(AGame &game, const Ray &ray) noexcept -> RaycastResult
{
	RaycastResult result{ false };
	double d;

	// TODO: cleaner with lambda template (after update to c++20)
	auto individualRaycastHandler = [&](entt::entity e, std::optional<Vector3> impact) {
		if (impact) {
			auto hitDistance = Vector3::distance(*impact, ray.start);

			if (!result.hit || hitDistance < d) {
				result.hit = true;
				result.impact = *impact;
				result.object = &game.getObject(e);

				d = hitDistance;
			}
		}
	};

#define CHECK_WITH(type) \
game.getWorld().view<type>().each([&](auto e, type &collider) { individualRaycastHandler(e, castRaycast(collider, ray)); });

	CHECK_WITH(SphereCollider);

#undef CHECK_WITH

	return result;
}
