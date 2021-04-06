#include <stdexcept>

#include "CG/Game.hpp"
#include "CG/internal/components/ICollider.hpp"
#include "CG/components/collider/SphereCollider.hpp"

CG::AGame::AGame(const CG::Vector2 windowSize, const std::string &windowName) : m_window(windowSize, windowName), m_inputManager(m_window.getWindow())
{
	if (AGame::instance)
		throw std::logic_error("Cannot run two game at once");
	AGame::instance = this;
}

void CG::AGame::forAllColliders(std::function<void(ICollider*)> func)
{
	m_world.view<SphereCollider>().each([func](auto _, SphereCollider &c) { func(&c); });
}

void CG::AGame::clearScene()
{
	for (auto &[e, obj] : m_objects)
		obj->destroy();
}

void CG::AGame::immediateDestroy(AGameObject::id_type obj)
{
	m_objects.erase(obj);
}
