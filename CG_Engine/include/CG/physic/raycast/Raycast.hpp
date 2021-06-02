#pragma once

#include <optional>

#include "CG/GameObject.hpp"
#include "CG/Game.hpp"
#include "CG/math/Ray.hpp"

namespace CG {

struct RaycastResult {
	bool hit;

	// Only initialized if `hit`
	GameObject *object = nullptr;
	Vector3 impact;
};


auto castRaycast(AGame &game, const Ray &ray) noexcept -> RaycastResult;

template <typename T>
std::optional<Vector3> castRaycastOn(const T &col, const CG::Transform &trans, const Ray &ray);

}

#include "algo/_all.inc"
