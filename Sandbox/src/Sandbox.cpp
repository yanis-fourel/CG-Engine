#include <fmt/format.h>

#include <imgui.h>

#include <CG/Color.hpp>
#include <CG/Vector3.hpp>

#include "Sandbox.hpp"

#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/Tile.hpp"
#include "GameObjects/TestCube.hpp"


void Sandbox::start()
{
	instanciate<FreeCameraManager>();

	m_gridColors.push_back(CG::Color{ 0.7f, 0.7f, 0.7f, 1.f });
	m_gridColors.push_back(CG::Color{ 0.3f, 0.3f, 0.3f, 1.f });

	m_gridSize = 10;

	m_tileSize = CG::Vector2{ 1, 1 };
}

void Sandbox::update(double deltatime)
{
	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();

	ImGui::Begin("Config");

	ImGui::Text(fmt::format("{:.1f} fps", 1/deltatime).c_str());

	if (ImGui::CollapsingHeader("Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::Text("Camera rotation is like a First person shooter game, with the mouse");
		ImGui::Text("You can toggle the mouse capture by pressing F1, so you can click on the options here");
		ImGui::Text("Camera movement is with WASD, plus E/Q for up/down");
	}

	if (ImGui::CollapsingHeader("Grid parameters", ImGuiTreeNodeFlags_DefaultOpen)) {
		m_shouldRegenerateGrid |= ImGui::SliderInt("Grid size", &m_gridSize, 1, 50);
		m_shouldRegenerateGrid |= ImGui::SliderFloat2("Tile size", reinterpret_cast<float *>(&m_tileSize), 0.1f, 5.0f);

		int toDelete = -1;

		int i = 0;
		for (auto &col : m_gridColors) {
			ImGui::PushID(i);

			m_shouldRegenerateGrid |= ImGui::ColorEdit4(fmt::format("[{}]", i).c_str(), reinterpret_cast<float *>(&col));
			ImGui::SameLine();

			if (m_gridColors.size() > 1 && ImGui::SmallButton("Delete")) {
				toDelete = i;
				m_shouldRegenerateGrid = true;
			}

			ImGui::PopID();
			i++;
		}

		if (toDelete != -1)
			m_gridColors.erase(std::begin(m_gridColors) + toDelete);

		if (ImGui::Button("Add")) {
			m_gridColors.push_back(CG::Color::White());
			m_shouldRegenerateGrid = true;
		}
	}



	ImGui::End();

	if (m_shouldRegenerateGrid) {
		regenerateGrid();
		m_shouldRegenerateGrid = false;
	}
}


void Sandbox::regenerateGrid()
{
	getObjectsOfTag<"tile"_hs>([](CG::AGameObject &obj) {
		obj.destroy();
		});


	CG::Vector3 tileScale{ m_tileSize.x, 0, m_tileSize.y };

	for (std::size_t x = 0; x < m_gridSize; ++x)
		for (std::size_t z = 0; z < m_gridSize; ++z)
			instanciate<Tile>(CG::Vector3{ x * tileScale.x, 0, z * tileScale.z }, tileScale, m_gridColors[(x + z) % m_gridColors.size()]);
}