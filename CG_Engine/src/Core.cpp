#include <stdexcept>

#include "CG/Core.hpp"
#include "CG/Camera.hpp"
#include "CG/Window.hpp"
#include "CG/ShaderManager.hpp"

#include "CG/internal/Shaders.hpp"

#include "CG/components/Updateable.hpp"

CG::Core::Core(std::unique_ptr<AGame> game) : m_game(std::move(game))
{}

int CG::Core::run()
{
	m_game->start();

	ShaderManager sm;

	sm.addShader(GL_VERTEX_SHADER, CG::shaders::simple_vert);
	sm.addShader(GL_FRAGMENT_SHADER, CG::shaders::simple_frag);
	sm.validate();


	while (m_game->getWindow().run()) {
		m_game->getInputManager().update();

		auto deltatime = 0.016; // like 60fps
		m_game->update(deltatime);

		m_game->getWorld().view<CG::Updateable>().each([deltatime](const CG::Updateable &u) {
			u.call(deltatime);
		});


		glm::mat4 model = glm::mat4(1);
		sm.uploadUniformMat4("model", model);
		sm.uploadUniformMat4("viewProj", m_game->getCamera().getViewProjMatrix());

		sm.use();
		// TODO: drawing
	}

	return 0;
}
