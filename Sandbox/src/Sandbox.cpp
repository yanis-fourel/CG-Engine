#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <iostream>

#include <imgui.h>

#include <CG/Color.hpp>
#include <CG/Vector3.hpp>
#include <CG/prefabs/PointLight.hpp>
#include <CG/ui/imfilebrowser.h>

#include "Sandbox.hpp"

#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/Tile.hpp"
#include "GameObjects/TestCube.hpp"
#include "GameObjects/Mesh.hpp"


void Sandbox::start()
{
	instanciate<FreeCameraManager>();
	//instanciate<TestCube>();
	instanciate<CG::prefabs::PointLight>(CG::Vector3{ 1, 5, 2 }, CG::Color::White());

	//instanciate<Mesh>("CrytekSponza/sponza.obj");
	//instanciate<Mesh>("bunny.obj");


	getGame()->setAmbiantLight(CG::Color(0.8f, 0.8f, 0.8f, 1.f));

	constexpr double height = -10;

	CG::Vector2 gridSize{ 20, 20 };
	for (int x = static_cast<int>(gridSize.x * -.5); x < gridSize.x * 0.5; ++x)
		for (int y = static_cast<int>(gridSize.y * -.5); y < gridSize.y * 0.5; ++y)
			instanciate<Tile>(CG::Vector3::Right() * x + CG::Vector3::Forward() * y + CG::Vector3::Up() * height, CG::Vector3{ 1.f, 0.f, 1.f }, (x + y) % 2 ? CG::Color(0.2f, 0.2f, 0.2f, 1) : CG::Color(0.7f, 0.7f, 0.7f, 1));

	m_fileBrowser.SetTitle("Browse file");
	m_fileBrowser.SetTypeFilters({ ".*" });
}

void Sandbox::update(double deltatime)
{
	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();

	if (getInputManager().isMouseCaptured())
		return;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(std::max(getWindow().getSize().x * 0.5f, 400.0f), getWindow().getSize().y));

	ImGui::Begin("Config");

	ImGui::Text(fmt::format("{:.1f} fps", 1 / deltatime).c_str());

	if (ImGui::CollapsingHeader("Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::TextColored(ImVec4(1, 0.5, 0.5, 1), "READ THIS FIRST");
		ImGui::Text("Camera movement is with WASD, plus E/Q for up/down");
		ImGui::Text("Camera rotation is like a First person shooter game, with the mouse");
		ImGui::Text("Camera rotation is paused while this screen is up");
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Press F1 to switch between scene config and FPS mode");
	}

	if (ImGui::Button("Pick a file"))
		m_fileBrowser.Open();

	ImGui::End();

	m_fileBrowser.Display();

	if (m_fileBrowser.HasSelected()) {
		const std::string picked = m_fileBrowser.GetSelected().string();

		spdlog::info("file picked : '{}'", picked);
		m_fileBrowser.Close();
	}

}

