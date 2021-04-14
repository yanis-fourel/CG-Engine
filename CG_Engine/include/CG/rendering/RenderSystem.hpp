#pragma once

#include <entt/fwd.hpp>

#include "CG/internal/ShaderProgram.hpp"
#include "CG/Game.hpp"

namespace CG::Renderer {

void renderScene(const AGame &game) noexcept;

namespace detail {
void uploadGlobalUniforms(const AGame &game) noexcept;
}

}
