#pragma once

#include <entt/entt.hpp>
#include <functional>
#include <cstdint>

#include "CG/Window.hpp"
#include "CG/AGameObject.hpp"
#include "CG/Camera.hpp"
#include "CG/InputManager.hpp"

#include "CG/Color.hpp"

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
	[[nodiscard]] auto getWorld() noexcept -> entt::registry &{ return m_world; }

	[[nodiscard]] auto getAmbiantLight() noexcept -> const Color & { return m_ambiantLight; }
	void setAmbiantLight(const Color &val) noexcept { m_ambiantLight = val; }

	template <typename T, typename... TArgs>
	T &instanciate(TArgs &&... args);

	template <std::uint32_t Tag>
	void getObjectsOfTag(std::function<void(AGameObject &)> func) noexcept;

	void getAllColliders(std::function<void(AGameObject &, ICollider *)> func) noexcept;

	// Destroys every single object of the scene
	void clearScene();

	// Call `obj.destroy()` unless you know what you're doing
	void immediateDestroy(AGameObject::id_type obj) noexcept;

	[[nodiscard]] auto isFrozen() const noexcept { return m_isFrozen; }
	void setFrozen(bool val) { m_isFrozen = val; }

	[[nodiscard]] auto getRealDeltatime() const noexcept { return m_realDeltaTime; }

	// You probably don't want to call that yourself
	void setRealDeltatime(double seconds) { m_realDeltaTime = seconds; }
public:
	static inline AGame *instance = nullptr;

private:
	Window m_window;
	InputManager m_inputManager;
	Camera m_camera;

	entt::registry m_world;
	std::unordered_map<AGameObject::id_type, std::unique_ptr<AGameObject>> m_objects;

	// TODO: move to a component or something
	Color m_ambiantLight { 0.2f, 0.2f, 0.2f };

	bool m_isFrozen = false;
	double m_realDeltaTime = 0;;
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
void CG::AGame::getObjectsOfTag(std::function<void(CG::AGameObject &)> func) noexcept
{
	for (auto id : m_world.view<entt::tag<Tag>>())
		func(*m_objects.at(id));
}
