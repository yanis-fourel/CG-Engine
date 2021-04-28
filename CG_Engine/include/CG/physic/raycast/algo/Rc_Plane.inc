#include <optional>

#include "CG/math/Vector3.hpp"
#include "CG/math/Ray.hpp"

#include "CG/components/collider/PlaneCollider.hpp"

namespace CG {

template <>
inline std::optional<Vector3> castRaycastOn<PlaneCollider>(const PlaneCollider &col, const CG::Transform &trans, const Ray &ray)
{
	auto normal = trans.rotation * col.normal;
	auto p0 = trans.position + col.point;

	auto denom = Vector3::dot(normal, ray.direction());

	if (denom >= 0)
		return {};

	    //float t = (center - ray.origin).dot(normal) / denom;
	double t = Vector3::dot(p0 - ray.start, normal) / denom;
	//auto t = (Vector3::dot(normal, p0) - Vector3::dot(normal, ray.start)) / denom;

	if (t < 0 || t > ray.length())
		return {};

	return ray.start + ray.direction() * t; // note : Slight precision loss
}

}
