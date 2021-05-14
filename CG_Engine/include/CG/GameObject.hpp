#pragma once

#include <entt/entt.hpp>
#include <string_view>

#include "CG/InputManager.hpp"
#include "CG/Camera.hpp"

namespace CG {

class AGame;

class GameObject {
public:
	using id_type = entt::registry::entity_type;

	GameObject();
	virtual ~GameObject();

	// Called once upon gameobject creation
	virtual void start() {};

	template<typename T>
	T &getComponent() noexcept;

	template<typename T>
	T *tryGetComponent() noexcept;

	[[nodiscard]] AGame *getGame() const noexcept;

	template <std::uint32_t Tag>
	[[nodiscard]] bool hasTag() const noexcept;

	auto getId() const noexcept { return static_cast<id_type>(m_entity); }

	void destroy() noexcept;

	template<typename T, typename... TArgs>
	T &addComponent(TArgs &&... args) noexcept;

	template<typename T, typename... TArgs>
	T &replaceComponent(TArgs &&... args) noexcept;

	template<typename T>
	void removeComponent() noexcept;

	template <std::uint32_t Tag>
	void setTag();

protected: // QoL getters
	template <typename Tag>
	void getObjectsOfTag(std::function<void(GameObject &)> func) const noexcept;

	InputManager *InputManager;
	Camera *GameCamera;

private:
	entt::registry::entity_type m_entity;
};


}

#include "CG/Game.hpp"

template<typename T>
T &CG::GameObject::getComponent() noexcept
{
	return getGame()->getWorld().get<T>(m_entity);
}

template<typename T>
T *CG::GameObject::tryGetComponent() noexcept
{
	return getGame()->getWorld().try_get<T>(m_entity);
}

template<typename T, typename... TArgs>
T &CG::GameObject::addComponent(TArgs &&... args) noexcept
{
	//  We could also store instances of base classes as
	//
	//if constexpr (std::is_base_of<ACollider, T>())
	//	getGame()->getWorld().emplace<AColliderGetter>([&](entt::entity e) -> ACollider * { return &getGame()->getWorld().get<T>(e); });
	//
	// which could be handled as override in `getComponent` to return the result of the call to previously stored lambda

	return getGame()->getWorld().emplace<T>(m_entity, std::forward<TArgs>(args)...);
}

template<typename T, typename ...TArgs>
inline T &CG::GameObject::replaceComponent(TArgs && ...args) noexcept
{
	return getGame()->getWorld().emplace_or_replace<T>(m_entity, std::forward<TArgs>(args)...);
}

template<typename T>
void CG::GameObject::removeComponent() noexcept
{
	getGame()->getWorld().remove<T>(m_entity);
}

template<std::uint32_t Tag>
void CG::GameObject::setTag()
{
	getGame()->getWorld().emplace<entt::tag<Tag>>(m_entity);
}

template<std::uint32_t Tag>
bool CG::GameObject::hasTag() const noexcept
{
	return getGame()->getWorld().has<entt::tag<Tag>>(m_entity);
}

template <typename Tag>
void CG::GameObject::getObjectsOfTag(std::function<void(GameObject &)> func) const noexcept
{
	getGame()->getObjectsOfTag<Tag>(func);
}
