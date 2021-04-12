#pragma once

#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "CG/components/Transform.hpp"
#include "CG/internal/ShaderManager.hpp"
#include "CG/Camera.hpp"

namespace CG
{

template<typename T>
concept Renderer = requires(T r, ShaderManager &sm)
{
	r.draw(sm);
};

template <Renderer T> 
inline void render(const T &r, const CG::Transform &t, ShaderManager &sm, const Camera &c)
{
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, static_cast<glm::vec3>(t.position));
	model *= glm::toMat4(static_cast<glm::quat>(t.rotation));
	model = glm::scale(model, static_cast<glm::vec3>(t.scale));

	sm.uploadUniformMat4("u_model", model);
	sm.uploadUniformMat4("u_modelViewMatrix", c.getViewMatrix() * model);
	sm.uploadUniformMat3("u_normalMatrix", glm::mat3(glm::transpose(glm::inverse(glm::mat3(model)))));

	r.draw(sm);
}

//#define ADD_RENDERER(type) \
//	m_game->getWorld().view<type, CG::Transform>().each([&](const type &r, const CG::Transform &t) { \
//		render(r, t, m_onlyShader, m_game->getCamera()); \
//		});
}