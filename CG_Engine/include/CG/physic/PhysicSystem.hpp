#pragma once

#include <entt/fwd.hpp>

#include "CG/Game.hpp"

namespace CG::physic {

void update(const AGame &game, double deltatime) noexcept;


namespace detail {

void resolveConstraints(const AGame &game) noexcept;
void resolveConstraintsOnce(const AGame &game) noexcept;
void handleCollision(entt::registry &world, entt::entity e1, entt::entity e2) noexcept;


void integrateAll(const AGame &game, double deltatime) noexcept;

}
}
