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
	instanciate<CG::prefabs::PointLight>(CG::Vector3{1, 5, 2}, CG::Color::White());
}

void Sandbox::update(double deltatime)
{
	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();

	
}

