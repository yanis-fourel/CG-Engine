#include "Sandbox.hpp"
#include "imgui.h"
#include "Cube.hpp"

void Sandbox::update(float deltatime)
{
	ImGui::ShowDemoWindow();

	if (ImGui::Begin("First window")) {
		ImGui::Text("Do you like it ?");

		ImGui::Button("Yes");
		ImGui::Button("No");
	}
	ImGui::End();

	Cube cube(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	cube.draw();
}
