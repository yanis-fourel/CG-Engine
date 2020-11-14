#include <stdexcept>

#include "CG/Game.hpp"

CG::AGame::AGame(const CG::Vector2 windowSize, const std::string &windowName) : m_window(windowSize, windowName), m_inputManager(m_window.getWindow())
{
	if (AGame::instance)
		throw std::logic_error("Cannot run two game at once");
	AGame::instance = this;
}

void CG::AGame::immediateDestroy(AGameObject::id_type obj)
{
	m_objects.erase(obj);
}
