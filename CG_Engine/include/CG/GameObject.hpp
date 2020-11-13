#pragma once

#include <entt/entt.hpp>

namespace CG {

class AGame;

class AGameObject {
public:
	AGameObject();
	virtual ~AGameObject();

	template<typename T>
	T &getComponent();

	[[nodiscard]] AGame *getGame() const noexcept;

protected:
	template<typename T, typename... TArgs>
	T &addComponent(TArgs &&... args);

	virtual void start() {};

private:
	entt::registry::entity_type m_entity;
};


}

#include "CG/Game.hpp"

template<typename T>
T &CG::AGameObject::getComponent()
{
	return getGame()->getWorld().get<T>(m_entity);
}

template<typename T, typename... TArgs>
T &CG::AGameObject::addComponent(TArgs &&... args)
{
	return getGame()->getWorld().emplace<T>(m_entity, std::forward<TArgs>(args)...);
}
