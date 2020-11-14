#include <stdexcept>

#include "CG/Core.hpp"
#include "CG/Camera.hpp"
#include "CG/Window.hpp"

#include "CG/internal/Shaders.hpp"

#include "CG/components/Updateable.hpp"
#include "CG/components/renderer/CubeRenderer.hpp"

CG::Core::Core(std::unique_ptr<AGame> game) : m_game(std::move(game))
{
	m_onlyShader.addShader(GL_VERTEX_SHADER, CG::shaders::simple_vert);
	m_onlyShader.addShader(GL_FRAGMENT_SHADER, CG::shaders::simple_frag);
	m_onlyShader.validate();
}

int CG::Core::run()
{
	m_game->start();

	while (m_game->getWindow().run()) {

		updateGame(0.016);
		displayGame();

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

void CG::Core::displayGame()
{
	// TODO: multiple shader management
	m_onlyShader.use();

	m_onlyShader.uploadUniformMat4("viewProj", m_game->getCamera().getViewProjMatrix());

	m_game->getWorld().view<CG::CubeRenderer>().each([&](const CG::CubeRenderer &u) {
		glm::mat4 model = glm::mat4(1); // TODO: make from gameobject transform
		m_onlyShader.uploadUniformMat4("model", model);
		u.draw();
	});

}