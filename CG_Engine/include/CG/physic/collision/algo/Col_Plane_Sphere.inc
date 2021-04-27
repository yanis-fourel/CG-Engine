#include "CG/components/collider/SphereCollider.hpp"
#include "CG/components/collider/PlaneCollider.hpp"
#include "CG/components/Transform.hpp"

template <>
auto CG::checkCollision(
	const Transform &t_plane, const PlaneCollider &col_plane,
	const Transform &t_sphere, const SphereCollider &col_sphere) noexcept -> std::optional<CollisionResult>
{
	Vector3 c0 = t_sphere.position + col_sphere.center;
	double radius = col_sphere.radius * (t_sphere.scale.x + t_sphere.scale.y + t_sphere.scale.z) / 3;

	Vector3 p0 = t_plane.position + col_plane.point;
	Vector3 n = (t_plane.rotation * col_plane.normal).normalized();

	auto distance = Vector3::dot(c0 - p0, n);

	n *= -1 + 2 * (distance > 0);
	// n is now properly the normal of impact
	distance = std::abs(distance);

	if (distance >= radius)
		return {};

	return CollisionResult {
		.hitNormal = n,
		.penetration = radius - distance 
	};
}
