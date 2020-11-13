#pragma once

#include <entt/entt.hpp>

#include "CG/Window.hpp"
#include "CG/GameObject.hpp"
#include "CG/Camera.hpp"
#include "CG/InputManager.hpp"

namespace CG {

class AGame {
public:
	AGame();

	[[nodiscard]] static inline AGame *getGame() noexcept { return instance; }

	virtual void start() {};
	virtual void update(double deltatime) {};

	[[nodiscard]] auto getWindow() -> Window &{ return m_window; }
	[[nodiscard]] auto getInputManager() -> InputManager &{ return m_inputManager; }
	[[nodiscard]] auto getCamera() -> Camera &{ return m_camera; }
	[[nodiscard]] auto getWorld() -> entt::registry &{ return m_world; }

	template <typename T, typename... TArgs>
	T &instanciate(TArgs &&... args);

public:
	static inline AGame *instance = nullptr;

private:
	Window m_window;
	InputManager m_inputManager;
	Camera m_camera;

	entt::registry m_world;
	std::vector<std::unique_ptr<AGameObject>> m_objects;
};

}

template <typename T, typename... TArgs>
T &CG::AGame::instanciate(TArgs &&... args)
{
	m_objects.emplace_back(std::make_unique<T>(std::forward<TArgs>(args)...));
	T &result = *dynamic_cast<T *>(m_objects.back().get());

	result.start();

	return result;
}
