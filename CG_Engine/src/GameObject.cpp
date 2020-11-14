#include "CG/GameObject.hpp"
#include "CG/Core.hpp"
#include "CG/Game.hpp"

CG::AGameObject::AGameObject() : m_entity(getGame()->getWorld().create())
{
	InputManager = &getGame()->getInputManager();
	GameCamera = &getGame()->getCamera();
}

CG::AGameObject::~AGameObject()
{
	getGame()->getWorld().destroy(m_entity);
}

CG::AGame *CG::AGameObject::getGame() const noexcept
{
	return AGame::instance;
}
