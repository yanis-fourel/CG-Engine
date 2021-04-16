#pragma once

#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "CG/components/Transform.hpp"
#include "CG/rendering/ShaderProgram.hpp"
#include "CG/Camera.hpp"

namespace CG::Renderer
{

inline void uploadModelMatrixes(const ShaderProgram &sp, const CG::Transform &t, const Camera &c) noexcept
{
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, static_cast<glm::vec3>(t.position));
	model *= glm::toMat4(static_cast<glm::quat>(t.rotation));
	model = glm::scale(model, static_cast<glm::vec3>(t.scale));

	sp.uploadUniformMat4("u_model", model);
	sp.uploadUniformMat4("u_modelViewMatrix", c.getViewMatrix() * model);
	sp.uploadUniformMat3("u_normalMatrix", glm::mat3(glm::transpose(glm::inverse(glm::mat3(model)))));
}

}