#include <stdexcept>

#include "CG/Game.hpp"
#include "CG/components/collider/SphereCollider.hpp"

CG::AGame::AGame(const CG::Vector2 windowSize, const std::string &windowName) : m_window(windowSize, windowName), m_inputManager(m_window.getWindow())
{
	if (AGame::instance)
		throw std::logic_error("Cannot run two game at once");
	AGame::instance = this;
}

auto CG::AGame::getObject(entt::entity e) -> GameObject &
{
	return *m_objects.at(e);
}

void CG::AGame::clearScene()
{
	for (auto &[e, obj] : m_objects)
		obj->destroy();
}

void CG::AGame::immediateDestroy(GameObject::id_type obj) noexcept
{
	m_objects.erase(obj);
}
