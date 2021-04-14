#pragma once

#include <entt/fwd.hpp>

#include "CG/internal/ShaderProgram.hpp"
#include "CG/Game.hpp"

namespace CG::Renderer {

void renderScene(ShaderProgram &onlyshader, const AGame &game) noexcept;

namespace detail {
void uploadGlobalUniforms(ShaderProgram &onlyshader, const AGame &game) noexcept;
}

}
