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

	m_onlyShader.uploadUniformMat4("viewProj", m_game->getCamera().getViewProjMatrix());


	m_game->getWorld().view<CG::CubeRenderer, CG::Transform>().each([&](const CG::CubeRenderer &u, const CG::Transform &t) {
		glm::mat4 model = glm::mat4(1); // TODO: make from gameobject transform
		model = glm::translate(model, static_cast<glm::vec3>(t.position));
		// TODO: rotation
		//		model = glm::rotate(model, );
		model = glm::scale(model, static_cast<glm::vec3>(t.scale));
		m_onlyShader.uploadUniformMat4("model", model);
		u.draw();
		});

	m_game->getWorld().view<CG::PlaneRenderer, CG::Transform>().each([&](const CG::PlaneRenderer &u, const CG::Transform &t) {
		glm::mat4 model = glm::mat4(1); // TODO: make from gameobject transform
		model = glm::translate(model, static_cast<glm::vec3>(t.position));
		// TODO: rotation
		//		model = glm::rotate(model, );
		model = glm::scale(model, static_cast<glm::vec3>(t.scale));
		m_onlyShader.uploadUniformMat4("model", model);
		u.draw();
		});
}
