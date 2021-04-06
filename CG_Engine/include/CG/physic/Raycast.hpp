#pragma once

#include <optional>

#include "CG/AGameObject.hpp"
#include "CG/Game.hpp"
#include "CG/math/Ray.hpp"

namespace CG {

struct RaycastResult {
	bool hit;

	// Only initialized if `hit`
	AGameObject *object = nullptr;
	Vector3 impact;
};


auto castRaycast(AGame &game, const Ray &ray) noexcept -> RaycastResult;

template <typename T>
std::optional<Vector3> castRaycast(const T &col, const Ray &ray);

}

#include "RaycastAlgo.inc"
