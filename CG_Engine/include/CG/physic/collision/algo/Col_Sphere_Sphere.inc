#include "CG/components/collider/SphereCollider.hpp"
#include "CG/components/Transform.hpp"

template <>
auto CG::checkCollision(
	const Transform &t1, const SphereCollider &col1,
	const Transform &t2, const SphereCollider &col2) noexcept -> std::optional<CollisionResult>
{
	auto center1 = t1.position + col1.center;
	auto center2 = t2.position + col2.center;

	auto radius1 = col1.radius * (t1.scale.x + t1.scale.y + t1.scale.z) / 3;
	auto radius2 = col2.radius * (t2.scale.x + t2.scale.y + t2.scale.z) / 3;

	auto centerDistance = Vector3::distance(center1, center2);
	auto radiusSum = radius1 + radius2;

	double penetration = radiusSum - centerDistance;

	if (penetration <= 0)
		return {};

	auto hitNormal = (center1 - center2).normalized();

	return CollisionResult {
		.hitNormal = hitNormal,
		.penetration = penetration
	};
}
