#pragma once

#include <optional>

#include "CG/math/Ray.hpp"
#include "CG/math/Vector3.hpp"

namespace CG {

class ICollider {
public:
	virtual ~ICollider() = default;

public:
	// returns collision point if any
	[[nodiscard]] virtual auto getIntersect(const Ray &r) const noexcept -> std::optional<Vector3> = 0;

};

}