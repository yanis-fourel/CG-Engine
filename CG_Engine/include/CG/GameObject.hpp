#pragma once

#include <entt/entt.hpp>
#include <string_view>

#include "CG/InputManager.hpp"
#include "CG/Camera.hpp"

namespace CG {

class AGame;

class AGameObject {
public:
	using id_type = entt::registry::entity_type;

	AGameObject();
	virtual ~AGameObject();

	// Called once upon gameobject creation
	virtual void start() {};

	template<typename T>
	T &getComponent();

	[[nodiscard]] AGame *getGame() const noexcept;

	auto getId() const noexcept { return static_cast<id_type>(m_entity); }

	void destroy() noexcept;
protected:
	template<typename T, typename... TArgs>
	T &addComponent(TArgs &&... args);

	template <std::uint32_t Tag>
	void setTag();

	// QoL getters
	template <typename Tag>
	void getObjectsOfTag(std::function<void(AGameObject &)> func) const noexcept;

	InputManager *InputManager;
	Camera *GameCamera;

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

template<std::uint32_t Tag>
void CG::AGameObject::setTag()
{
	getGame()->getWorld().emplace<entt::tag<Tag>>(m_entity);
}

template <typename Tag>
void CG::AGameObject::getObjectsOfTag(std::function<void(AGameObject &)> func) const noexcept
{
	getGame()->getObjectsOfTag<Tag>(func);
}
