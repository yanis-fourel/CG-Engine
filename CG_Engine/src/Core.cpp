#include <stdexcept>
#include <chrono>

#include <glm/gtx/transform.hpp>

#include "CG/Core.hpp"
#include "CG/Camera.hpp"
#include "CG/Window.hpp"

#include "CG/internal/Shaders.hpp"

#include "CG/internal/ToDelete.hpp"
#include "CG/components/Updateable.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/renderer/CubeRenderer.hpp"
#include "CG/components/renderer/PlaneRenderer.hpp"

#include "CG/RendererHelper.hpp"

CG::Core::Core(std::unique_ptr<AGame> game) : m_game(std::move(game))
{
	m_onlyShader.addShader(GL_VERTEX_SHADER, CG::shaders::simple_vert);
	m_onlyShader.addShader(GL_FRAGMENT_SHADER, CG::shaders::simple_frag);
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

#define ADD_RENDERER(type) \
	m_game->getWorld().view<type, CG::Transform>().each([&](const type &r, const CG::Transform &t) { \
		render(r, t, m_onlyShader, m_game->getCamera()); \
		});

	ADD_RENDERER(CG::CubeRenderer);
	ADD_RENDERER(CG::PlaneRenderer);

#undef ADD_RENDERER
}
