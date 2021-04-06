#include <optional>

#include "CG/physic/Raycast.hpp"

#include "CG/math/Vector3.hpp"
#include "CG/math/Ray.hpp"

#include "CG/components/collider/PlaneCollider.hpp"

namespace CG {

template <>
inline std::optional<Vector3> castRaycastOn<PlaneCollider>(const PlaneCollider &col, const Ray &ray)
{
	auto normal = col.transform->rotation * Vector3::Forward();
	auto p0 = col.transform->position;

	auto denom = Vector3::dot(normal, ray.direction());

	if (denom <= 0)
		return {};

	auto t = (Vector3::dot(normal, p0) - Vector3::dot(normal, ray.start)) / denom;

	if (t < 0 || t > ray.length())
		return {};

	return ray.start + ray.direction() * t; // note : Slight precision loss
}

}
