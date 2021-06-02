#pragma once


#include <entt/fwd.hpp>

#include "CG/Game.hpp"
#include "CG/rendering/Material.hpp"
#include "CG/rendering/ShaderProgram.hpp"

namespace CG::Renderer {

void renderScene(const AGame &game) noexcept;

namespace detail {

void uploadGlobalUniforms(const AGame &game) noexcept;

}

}
