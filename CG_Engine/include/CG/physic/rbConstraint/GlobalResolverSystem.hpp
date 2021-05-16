#pragma once

//
// A Global resolver solves constaints between ALL object having Transform, Rigidbody and Collider
// by calling a local resolver on each object pair in the scene
//

#include <entt/entt.hpp>

#include "LocalResolver.hpp"

namespace CG::physic {

namespace detail {
template <bool callEvent, typename T1, typename T2, typename ...Others> void matchAllColliders_2(entt::registry &world);
template <bool callEvent, typename T1, typename ...Others>				void matchAllColliders_1(entt::registry &world);
}


template <bool callEvent, typename ...Colliders>
void globalConstraintSolver(entt::registry &world)
{
	detail::matchAllColliders_1<callEvent, Colliders...>(world);
	detail::matchAllColliders_2<callEvent, Colliders...>(world);
}


namespace detail {

void callOnCollideEvent(GameObject &obj1, GameObject &obj2)
{
	obj1.onCollide(obj2);
	obj2.onCollide(obj1);
}

template <bool callEvent, typename Col1, typename Col2>
void matchAllEntities_2(entt::registry &world) noexcept
{
	auto v1 = world.view<Transform, Rigidbody, Col1>();
	auto v2 = world.view<Transform, Rigidbody, Col2>();

	v1.each([&](auto e1, auto &t1, auto &rb1, auto &col1) {
		v2.each([&](auto e2, auto &t2, auto &rb2, auto &col2) {
			auto collide = CG::physic::localConstraintSolver(t1, rb1, col1, t2, rb2, col2);

			if constexpr (callEvent)
				if (collide)
					callOnCollideEvent(AGame::getGame()->getObject(e1), AGame::getGame()->getObject(e2));
			});
		});
}

template <bool callEvent, typename Col>
void matchAllEntities_1(entt::registry &world) noexcept
{
	//if constexpr (std::is_same<Col, CG::PlaneCollider>())
	//	return;

	std::vector<std::tuple<entt::entity, Transform *, Rigidbody *, Col *>> entities;

	{
		auto v = world.view<Transform, Rigidbody, Col>();
		v.each([&](auto e, Transform &t, Rigidbody &rb, Col &c) {
			entities.emplace_back(e, &t, &rb, &c);
			});
	}

	for (auto i = 0u; i < entities.size(); i++) {
		auto [e1, t1, rb1, col1] = entities[i];

		for (auto j = i + 1; j < entities.size(); j++)
		{
			auto [e2, t2, rb2, col2] = entities[j];

			auto collide = CG::physic::localConstraintSolver(*t1, *rb1, *col1, *t2, *rb2, *col2);

			if constexpr (callEvent)
				if (collide)
					callOnCollideEvent(AGame::getGame()->getObject(e1), AGame::getGame()->getObject(e2));
		}
	}
}

template <bool callEvent, typename T1, typename T2, typename ...Others>
void matchAllColliders_2(entt::registry &world)
{
	matchAllEntities_2<callEvent, T1, T2>(world);

	if constexpr (sizeof...(Others) > 0) {
		matchAllEntities_2<callEvent, T1, Others...>(world);
		matchAllEntities_2<callEvent, T2, Others...>(world);
	}
}

template <bool callEvent, typename T1, typename ...Others>
void matchAllColliders_1(entt::registry &world)
{
	matchAllEntities_1<callEvent, T1>(world);

	if constexpr (sizeof...(Others) > 0) {
		matchAllEntities_1<callEvent, Others...>(world);
	}
}

}

}
