#include <stdexcept>
#include <chrono>

#include <glm/gtx/transform.hpp>

#include "CG/Core.hpp"
#include "CG/Camera.hpp"
#include "CG/Window.hpp"

#include "CG/internal/ToDelete.hpp"
#include "CG/components/Updateable.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/PointLight.hpp"

#include "CG/components/renderer/CubeRenderer.hpp"
#include "CG/components/renderer/PlaneRenderer.hpp"
#include "CG/components/renderer/SphereRenderer.hpp"
#include "CG/components/renderer/MeshRenderer.hpp"

#include "CG/RendererHelper.hpp"

CG::Core::Core(std::unique_ptr<AGame> game) : m_game(std::move(game))
{
	m_onlyShader.addShader(GL_VERTEX_SHADER, "vert.glsl");
	m_onlyShader.addShader(GL_FRAGMENT_SHADER, "frag.glsl");
	m_onlyShader.validate();
}

int CG::Core::run()
{
	m_game->start();

	double deltatime = 0;

	while (m_game->getWindow().run()) {
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		updateGame(deltatime);

		cleanupDeadGameobjects();

		displayGame();

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		deltatime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 1e-9;
	}

	return 0;
}

void CG::Core::updateGame(double deltatime)
{
	m_game->getInputManager().update();

	m_game->update(deltatime);

	m_game->getWorld().view<CG::Updateable>().each([deltatime](const CG::Updateable &u) {
		u.call(deltatime);
		});

}

void CG::Core::cleanupDeadGameobjects()
{
	for (const auto &e : m_game->getWorld().view<CG::ToDelete>())
		m_game->immediateDestroy(e);
}

void CG::Core::displayGame()
{
	// TODO: multiple shader management
	m_onlyShader.use();

	m_onlyShader.uploadUniformMat4("u_viewProj", m_game->getCamera().getViewProjMatrix());
	m_onlyShader.uploadUniformVec3("u_ambiantLightColor", m_game->getAmbiantLight().toVec3());
	m_onlyShader.uploadUniformVec3("u_eyePos", m_game->getCamera().getPosition());

	{ // Point light

		// TODO: Support multiple lights and multiple light types
		glm::vec4 lightPos;
		CG::Color lightColor;

		m_game->getWorld().view<CG::PointLight, CG::Transform>().each([&](const auto &light, const auto t) {
			lightColor = light.color;
			lightPos = glm::vec4(static_cast<glm::vec3>(t.position), 1.0);
		});

		m_onlyShader.uploadUniformVec4("u_pointLightPosition", lightPos);
		m_onlyShader.uploadUniformVec3("u_pointLightColor", lightColor.toVec3());
	}


#define ADD_RENDERER(type) \
	m_game->getWorld().view<type, CG::Transform>().each([&](const type &r, const CG::Transform &t) { \
		render(r, t, m_onlyShader, m_game->getCamera()); \
		});

	ADD_RENDERER(CG::CubeRenderer);
	ADD_RENDERER(CG::PlaneRenderer);
	ADD_RENDERER(CG::SphereRenderer);
	ADD_RENDERER(CG::MeshRenderer);

#undef ADD_RENDERER
}
