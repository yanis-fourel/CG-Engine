#pragma once

#include <entt/entt.hpp>
#include <functional>
#include <cstdint>
#include <ranges>

#include "CG/Window.hpp"
#include "CG/GameObject.hpp"
#include "CG/Camera.hpp"
#include "CG/InputManager.hpp"

#include "CG/Color.hpp"
#include "CG/internal/components/ToDelete.hpp"

namespace CG {

class ICollider;

class AGame {
public:
	AGame(const CG::Vector2 windowSize = { 640, 480 }, const std::string &windowName = "CG Application");

	[[nodiscard]] static inline AGame *getGame() noexcept { return instance; }

	virtual void start() {};
	virtual void update(double deltatime) {};

	[[nodiscard]] auto getWindow() noexcept -> Window &{ return m_window; }
	[[nodiscard]] auto getInputManager()noexcept -> InputManager &{ return m_inputManager; }
	[[nodiscard]] auto getCamera() noexcept -> Camera &{ return m_camera; }
	[[nodiscard]] auto getCamera() const noexcept -> const Camera &{ return m_camera; }
	[[nodiscard]] auto getWorld() const noexcept -> entt::registry &{ return m_world; }

	[[nodiscard]] auto getAmbiantLight() const noexcept -> const Color &{ return m_ambiantLight; }
	void setAmbiantLight(const Color &val) noexcept { m_ambiantLight = val; }

	template <typename T, typename... TArgs>
	T &instanciate(TArgs &&... args);

	template <std::uint32_t Tag>
	void getObjectsOfTag(std::function<void(GameObject &)> func) noexcept;

	[[nodiscard]] auto getObject(entt::entity e)->GameObject &;
	void forEachObj(std::function<void(GameObject &obj)> func);

	// Destroys every single object of the scene
	void clearScene();

	// Call `obj.destroy()` unless you know what you're doing
	void immediateDestroy(GameObject::id_type obj) noexcept;

	[[nodiscard]] auto isFrozen() const noexcept { return m_isFrozen; }
	void setFrozen(bool val) { m_isFrozen = val; }

	[[nodiscard]] auto getRealDeltatime() const noexcept { return m_realDeltaTime; }
	[[nodiscard]] auto getGlobalTimeFactor() const noexcept { return m_globalTimeFactor; }

	void setGlobalTimeFactor(double fact) { m_globalTimeFactor = fact; }

CG_INTERNAL_METHOD:
	void setRealDeltatime(double seconds) { m_realDeltaTime = seconds; }
public:
	static inline AGame *instance = nullptr;

private:
	Window m_window;
	InputManager m_inputManager;
	Camera m_camera;

	mutable entt::registry m_world;
	std::unordered_map<GameObject::id_type, std::unique_ptr<GameObject>> m_objects;

	// TODO: move to a component or something
	Color m_ambiantLight{ 0.2f, 0.2f, 0.2f };

	bool m_isFrozen = false;
	double m_realDeltaTime = 0;
	double m_globalTimeFactor = 1;
};

}

template <typename T, typename... TArgs>
T &CG::AGame::instanciate(TArgs &&... args)
{
	auto ptr = std::make_unique<T>(std::forward<TArgs>(args)...);
	T &result = *ptr;

	m_objects[ptr->getId()] = std::move(ptr);

	result.start();
	return result;
}

template<std::uint32_t Tag>
void CG::AGame::getObjectsOfTag(std::function<void(CG::GameObject &)> func) noexcept
{
	for (auto id : m_world.view<entt::tag<Tag>>(entt::exclude<CG::ToDelete>))
		func(*m_objects.at(id));
}
