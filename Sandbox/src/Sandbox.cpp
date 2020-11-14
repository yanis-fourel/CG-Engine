#include "Sandbox.hpp"
#include "imgui.h"

#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/TestCube.hpp"

void Sandbox::start()
{
	instanciate<FreeCameraManager>();
	instanciate<TestCube>();
}

void Sandbox::update(double deltatime)
{
	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();
}
