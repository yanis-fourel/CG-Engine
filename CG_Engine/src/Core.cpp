#include <stdexcept>
#include <chrono>
#include <spdlog/spdlog.h>

#include <glm/gtx/transform.hpp>

#include "CG/Core.hpp"
#include "CG/Camera.hpp"
#include "CG/Window.hpp"

#include "CG/internal/components/ToDelete.hpp"
#include "CG/components/OnUpdate.hpp"
#include "CG/components/OnLateUpdate.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/PointLight.hpp"

#include "CG/physic/PhysicSystem.hpp"
#include "CG/rendering/RenderSystem.hpp"

CG::Core::Core(std::unique_ptr<AGame> game) : m_game(std::move(game))
{}

int CG::Core::run()
{
	m_game->start();

	double deltatime = 0;

	while (m_game->getWindow().run()) {
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		tick(m_game->isFrozen() ? 0 : deltatime * m_game->getGlobalTimeFactor());

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		deltatime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() * 1e-9;
		m_game->setRealDeltatime(deltatime);
	}

	return 0;
}

void CG::Core::tick(double deltatime)
{
	m_game->getInputManager().update();

	updateGame(deltatime);
	physic::update(*m_game, deltatime);
	lateUpdate(deltatime);

	cleanupDeadGameobjects();

	CG::Renderer::renderScene(*m_game);
}

void CG::Core::updateGame(double deltaGametime)
{
	m_game->update(deltaGametime);

	m_game->getWorld().view<CG::OnUpdate>().each([deltaGametime](const CG::OnUpdate &u) {
		u.call(deltaGametime);
		});
}

void CG::Core::cleanupDeadGameobjects()
{
	for (const auto &e : m_game->getWorld().view<CG::ToDelete>())
		m_game->immediateDestroy(e);
}

void CG::Core::lateUpdate(double deltaGametime)
{
	m_game->getWorld().view<CG::OnLateUpdate>().each([deltaGametime](const CG::OnLateUpdate &u) {
		u.call(deltaGametime);
		});
}
