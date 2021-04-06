#include "CG/components/collider/SphereCollider.hpp"

CG::SphereCollider::SphereCollider(const Transform *transform) : m_transform(transform)
{}

auto CG::SphereCollider::getIntersect(const Ray &r) const noexcept -> std::optional<Vector3>
{
	// TODO respect actual scale
	auto radius = (m_transform->scale.x + m_transform->scale.y + m_transform->scale.z) / 3 * 0.5;

	auto delta = std::pow(Vector3::dot(r.direction(), r.start - m_transform->position), 2) - std::pow((r.start - m_transform->position).magnitude(), 2) + radius*radius;

	if (delta < 0)
		return {};

	auto d1 = -(Vector3::dot(r.direction(), r.start - m_transform->position)) + std::sqrt(delta);
	auto d2 = -(Vector3::dot(r.direction(), r.start - m_transform->position)) - std::sqrt(delta);

	auto d = std::min(d1, d2);

	if (d < 0 || d > r.length())
		return {};

	auto p = r.start + r.direction() * d;

	return p;
}
