#include <stdexcept>

#include "CG/Game.hpp"

CG::AGame::AGame() : m_inputManager(m_window.getWindow())
{
	if (AGame::instance)
		throw std::logic_error("Cannot run two game at once");
	AGame::instance = this;
}
