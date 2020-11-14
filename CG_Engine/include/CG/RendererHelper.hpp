#pragma once

#include <glm/gtx/transform.hpp>

#include "CG/components/Transform.hpp"
#include "CG/ShaderManager.hpp"

namespace CG
{

template <typename Renderer>
inline void render(const Renderer &r, const CG::Transform &t, ShaderManager &sm)
{
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, static_cast<glm::vec3>(t.position));
	// TODO: rotation
	//		model = glm::rotate(model, );
	model = glm::scale(model, static_cast<glm::vec3>(t.scale));
	sm.uploadUniformMat4("model", model);
	r.draw();
}

}