#include "CG/physic/Raycast.hpp"
#include "CG/internal/components/ICollider.hpp"
#include "CG/AGameobject.hpp"

auto CG::castRaycast(AGame & game, const Ray & ray) noexcept -> RaycastResult
{
	RaycastResult result { false };
	double d;

	game.getAllColliders([&](AGameObject &obj, ICollider *c) {
		auto hitPos = c->getIntersect(ray);

		if (hitPos) {
			auto hitDistance = Vector3::distance(*hitPos, ray.start);

			if (!result.hit || hitDistance < d) {
				result.hit = true;
				result.impact = *hitPos;
				result.object = &obj;

				d = hitDistance;
			}
		}
	});

	return result;
}
