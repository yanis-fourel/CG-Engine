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


template <typename Col1, typename Col2>
void handleCollisionCheck_2() noexcept
{
	spdlog::info("Checking collision between all {} and {}", typeid(Col1).name(), typeid(Col2).name());

	//auto v = game.getWorld().view<Transform, Rigidbody, SphereCollider>();

	//return checkCollision(t2, col2, t1, col1);
}

template <typename Col>
void handleCollisionCheck_1() noexcept
{
	spdlog::info("Checking collision whithin all {}", typeid(Col).name());

	//auto v = game.getWorld().view<Transform, Rigidbody, Col>();

	//for (auto it = v.begin(); it != v.end(); ) {
	//	auto e1 = *it;

	//	it++;
	//	for (auto it2 = it; it2 != v.end(); it2++)
	//		handleCollision(game.getWorld(), e1, *it2);
	//}
}

template <typename T1, typename T2, typename ...Others>
void handleCollisionChecks_2()
{
	handleCollisionCheck_2<T1, T2>();

	if constexpr (sizeof...(Others) > 0) {
		handleCollisionChecks_2<T1, Others...>();
		handleCollisionChecks_2<T2, Others...>();
	}
}

template <typename T1, typename ...Others>
void handleCollisionChecks_1()
{
	handleCollisionCheck_1<T1>();

	if constexpr (sizeof...(Others) > 0) {
		handleCollisionChecks_1<Others...>();
	}
}

template <typename ...Colliders>
void handleCollisionChecks()
{
	handleCollisionChecks_1<Colliders...>();
	handleCollisionChecks_2<Colliders...>();
}

}

#include "algo/_all.inc"
