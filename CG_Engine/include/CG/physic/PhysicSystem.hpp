#pragma once

#include <entt/fwd.hpp>
#include <spdlog/spdlog.h>

#include "CG/Game.hpp"

namespace CG::physic {

void update(const AGame &game, double deltatime) noexcept;


namespace detail {

void resolveConstraints(const AGame &game) noexcept;

void integrateAll(const AGame &game, double deltatime) noexcept;



}
}
