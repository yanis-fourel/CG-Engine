#pragma once

#include "CG/internal/components/ICollider.hpp"
#include "CG/components/Transform.hpp"

namespace CG {

class SphereCollider : public ICollider
{
public:
	explicit SphereCollider(const Transform *transform);

	[[nodiscard]] auto getIntersect(const Ray &r) const noexcept -> std::optional<Vector3> override;

private:
	const Transform *m_transform;
};

}
