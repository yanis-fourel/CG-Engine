#pragma once

#include <optional>
#include <spdlog/spdlog.h>

#include "collisionResult.hpp"
#include "CG/components/Transform.hpp"


namespace CG {

// Each collider type pair has a defined implementation
template <typename Col1, typename Col2>
auto checkCollision(const Transform &t1, const Col1 &col1, const Transform &t2, const Col2 &col2) noexcept -> std::optional<CollisionResult>
{
	return checkCollision(t2, col2, t1, col1);
}

}

#include "algo/_all.inc"
