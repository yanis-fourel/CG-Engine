#include <optional>

#include "CG/physic/Raycast.hpp"

#include "CG/math/Vector3.hpp"
#include "CG/math/Ray.hpp"

#include "CG/components/collider/SphereCollider.hpp"


//
// This file contain template specialisation to compute intersection between a ray and every type of collider
//


namespace CG {

template <>
inline std::optional<Vector3> castRaycast<SphereCollider>(const SphereCollider &col, const Ray &ray)
{
// TODO respect actual scale
	auto radius = (col.transform->scale.x + col.transform->scale.y + col.transform->scale.z) / 3 * 0.5;
	auto position = col.transform->position;

	auto delta = std::pow(Vector3::dot(ray.direction(), ray.start - position), 2) - std::pow((ray.start - position).magnitude(), 2) + radius*radius;

	if (delta < 0)
		return {};

	auto d1 = -(Vector3::dot(ray.direction(), ray.start - position)) + std::sqrt(delta);
	auto d2 = -(Vector3::dot(ray.direction(), ray.start - position)) - std::sqrt(delta);

	auto d = std::min(d1, d2);

	if (d < 0 || d > ray.length())
		return {};

	auto p = ray.start + ray.direction() * d;

	return p;
}


}
