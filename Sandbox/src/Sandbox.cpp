#include "Sandbox.hpp"
#include "imgui.h"

#include "GameObjects/FreeCamera.hpp"
#include "GameObjects/TestCube.hpp"

void Sandbox::start()
{
	instanciate<FreeCamera>();
	instanciate<TestCube>();
}

void Sandbox::update(double deltatime)
{
	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();
}
