#pragma once

#include <entt/fwd.hpp>

#include "CG/internal/ShaderManager.hpp"
#include "CG/Game.hpp"

namespace CG::Renderer {

void renderScene(ShaderManager &onlyshader, const AGame &game) noexcept;

}