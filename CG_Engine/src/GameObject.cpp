#include "CG/GameObject.hpp"
#include "CG/Core.hpp"
#include "CG/Game.hpp"

#include "CG/internal/components/ToDelete.hpp"

CG::GameObject::GameObject() : m_entity(getGame()->getWorld().create())
{
	InputManager = &getGame()->getInputManager();
	GameCamera = &getGame()->getCamera();
}

CG::GameObject::~GameObject()
{
	getGame()->getWorld().destroy(m_entity);
}

CG::AGame *CG::GameObject::getGame() const noexcept
{
	return AGame::instance;
}

void CG::GameObject::destroy() noexcept
{
	addComponent<CG::ToDelete>();
}
