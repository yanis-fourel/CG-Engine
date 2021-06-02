#include "CG/components/collider/PlaneCollider.hpp"


// Ignore for now, Planes are infinite so checking their collisions don't make much sense


template <>
auto CG::checkCollision(
	const Transform &t1, const PlaneCollider &c1,
	const Transform &t2, const PlaneCollider &c2) noexcept -> std::optional<CollisionResult>
{
	return {}; 
}
