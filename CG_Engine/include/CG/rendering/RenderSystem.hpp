#pragma once


#include <entt/fwd.hpp>

#include "CG/Game.hpp"
#include "CG/internal/Material.hpp"
#include "CG/internal/ShaderProgram.hpp"
#include "CG/components/Transform.hpp"

namespace CG::Renderer {

void renderScene(const AGame &game) noexcept;

namespace detail {

void uploadGlobalUniforms(const AGame &game) noexcept;

void display(const AGame &game, entt::entity entity, const ::CG::AMaterial &material, const ::CG::Transform &transform) noexcept;

}

}
