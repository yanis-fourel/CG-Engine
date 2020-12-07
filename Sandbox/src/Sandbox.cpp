#include <fmt/format.h>

#include <imgui.h>

#include <CG/Color.hpp>
#include <CG/Vector3.hpp>
#include <CG/prefabs/PointLight.hpp>

#include "Sandbox.hpp"

#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/Tile.hpp"
#include "GameObjects/TestCube.hpp"


void Sandbox::start()
{
	instanciate<FreeCameraManager>();
	instanciate<TestCube>();
	instanciate<CG::prefabs::PointLight>(CG::Vector3{ 1, 5, 2 }, CG::Color::White());

	getGame()->setAmbiantLight(CG::Color(0.3, 0.3, 0.3, 0.1));

	CG::Vector2 gridSize{20, 20};
	for (int x = static_cast<int>(gridSize.x * -.5); x < gridSize.x * 0.5; ++x)
		for (int y = static_cast<int>(gridSize.y * -.5); y < gridSize.y * 0.5; ++y)
			instanciate<Tile>(CG::Vector3::Right() * x + CG::Vector3::Forward() * y, CG::Vector3{1.f, 0.f, 1.f}, (x + y) % 2 ? CG::Color(0.2f, 0.2f, 0.2f, 1) : CG::Color(0.7f, 0.7f, 0.7f, 1));
}

void Sandbox::update(double deltatime)
{
	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();


}

