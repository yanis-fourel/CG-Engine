#include "CG/components/collider/SphereCollider.hpp"
#include "CG/components/collider/PlaneCollider.hpp"
#include "CG/components/Transform.hpp"

template <>
auto CG::checkCollision(
	const Transform &t_plane, const PlaneCollider &col_plane,
	const Transform &t_sphere, const SphereCollider &col_sphere) noexcept -> std::optional<CollisionResult>
{
	return {}; // TODO
}
