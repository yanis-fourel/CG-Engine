#include "CG/components/collider/PlaneCollider.hpp"
#include "CG/components/Transform.hpp"

template <>
auto CG::checkCollision(
	const Transform &t1, const PlaneCollider &c1,
	const Transform &t2, const PlaneCollider &c2) noexcept -> std::optional<CollisionResult>
{
	return {}; // TODO
}
