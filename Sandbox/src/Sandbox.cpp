#include "Sandbox.hpp"
#include "imgui.h"
#include "Cube.hpp"
#include "GameObjects/FreeCamera.hpp"

void Sandbox::start()
{
	instanciate<FreeCamera>();
}

void Sandbox::update(double deltatime)
{
	ImGui::ShowDemoWindow();

	if (ImGui::Begin("First window")) {
		ImGui::Text("Do you like it ?");

		ImGui::Button("Yes");
		ImGui::Button("No");
	}
	ImGui::End();

	Cube cube(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	cube.draw(); // TODO: move to engine


	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();
}
