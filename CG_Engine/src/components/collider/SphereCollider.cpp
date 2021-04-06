#include "CG/components/collider/SphereCollider.hpp"

CG::SphereCollider::SphereCollider(const Transform *transform) : m_transform(transform)
{}

auto CG::SphereCollider::getIntersect(const Ray &r) const noexcept -> std::optional<Vector3>
{
	// TODO respect actual scale
	float radius = m_transform->scale.magnitude();

	auto rayDir = (r.finish - r.start).normalized();

	auto delta = std::pow(rayDir.dot(r.start - m_transform->position), 2) - std::pow((r.start - m_transform->position).magnitude(), 2) + radius*radius;

	if (delta < 0)
		return {};

	auto d1 = -(r.direction().dot(r.start - m_transform->position)) + std::sqrt(delta);
	auto d2 = -(r.direction().dot(r.start - m_transform->position)) - std::sqrt(delta);

	auto d = std::min(d1, d2);

	if (d < 0 || d > r.length())
		return {};

	auto p = r.start + r.direction() * d;

	return p;
}
