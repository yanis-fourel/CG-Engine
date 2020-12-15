#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <iostream>

#include <imgui.h>

#include <CG/Color.hpp>
#include <CG/Vector3.hpp>
#include <CG/prefabs/PointLight.hpp>
#include <CG/ui/imfilebrowser.h>

#include "CG/components/PointLight.hpp"
#include "CG/components/Transform.hpp"

#include "Sandbox.hpp"

#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/Tile.hpp"
#include "GameObjects/TestCube.hpp"
#include "GameObjects/Mesh.hpp"
#include "AssetDir.hpp"


void Sandbox::start()
{
	instanciate<FreeCameraManager>();
	//instanciate<TestCube>();
	m_pointLight = &instanciate<CG::prefabs::PointLight>(CG::Vector3{ 1, 5, 2 }, CG::Color::White());

	m_meshes.push_back(&instanciate<Mesh>("bunny.obj"));


	getGame()->setAmbiantLight(CG::Color(0.8f, 0.8f, 0.8f, 1.f));

	constexpr double height = -10;

	CG::Vector2 gridSize{ 20, 20 };
	for (int x = static_cast<int>(gridSize.x * -.5); x < gridSize.x * 0.5; ++x)
		for (int y = static_cast<int>(gridSize.y * -.5); y < gridSize.y * 0.5; ++y)
			instanciate<Tile>(CG::Vector3::Right() * x + CG::Vector3::Forward() * y + CG::Vector3::Up() * height, CG::Vector3{ 1.f, 0.f, 1.f }, (x + y) % 2 ? CG::Color(0.2f, 0.2f, 0.2f, 1) : CG::Color(0.7f, 0.7f, 0.7f, 1));

	m_fileBrowser.SetTitle("Browse file");
}

void Sandbox::update(double deltatime)
{
	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();

	if (getInputManager().isMouseCaptured())
		return;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(std::max(getWindow().getSize().x * 0.5f, 400.0f), getWindow().getSize().y));
	ImGui::SetNextWindowBgAlpha(0);

	ImGui::Begin("Config", nullptr, ImGuiWindowFlags_NoDecoration);

	ImGui::Text(fmt::format("{:.1f} fps", 1 / deltatime).c_str());

	if (ImGui::CollapsingHeader("Controls", ImGuiTreeNodeFlags_DefaultOpen)) {
		ImGui::TextColored(ImVec4(1, 0.5, 0.5, 1), "READ THIS FIRST");
		ImGui::Text("Camera movement is with WASD, plus E/Q for up/down");
		ImGui::Text("Camera rotation is like a First person shooter game, with the mouse");
		ImGui::Text("Camera rotation is paused while this screen is up");
		ImGui::Text("Press left shift to fo faster");
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Press F1 to switch between scene config and FPS mode");
	}

	if (ImGui::CollapsingHeader("Lights")) {
		// ambiant light
		{
			CG::Color c = getAmbiantLight();
			if (ImGui::ColorEdit4("Ambiant light", reinterpret_cast<float *>(&c)))
				setAmbiantLight(c);
		}

		// point light
		{
			auto &color = m_pointLight->getComponent<CG::PointLight>().color;
			auto &transform = m_pointLight->getComponent<CG::Transform>();

			ImGui::ColorEdit4("Point light color", reinterpret_cast<float *>(&color));

			ImGui::DragFloat3("Point light position", reinterpret_cast<float *>(&transform.position), 0.1);
			if (ImGui::Button("Set to camera position"))
				transform.position = getCamera().getPosition();
		}
	}


	if (ImGui::CollapsingHeader("Meshes", ImGuiTreeNodeFlags_DefaultOpen)) {

		std::size_t toDelete = m_meshes.size();
		for (unsigned i = 0; i < m_meshes.size(); ++i) {
			ImGui::PushID(i);

			ImGui::Text(m_meshes[i]->getPath().c_str());

			auto &transform = m_meshes[i]->getComponent<CG::Transform>();

			ImGui::DragFloat3("Scale", reinterpret_cast<float *>(&transform.scale), 0.01f);
			ImGui::DragFloat3("Position", reinterpret_cast<float *>(&transform.position), 0.01f);
			if (ImGui::Button("Set to camera position"))
				transform.position = getCamera().getPosition();


			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.2f, 0.2f, 1.f));
			if (ImGui::Button("Delete"))
				toDelete = i;
			ImGui::PopStyleColor();

			ImGui::PopID();

			ImGui::Separator();
		}

		if (toDelete != m_meshes.size()) {
			m_meshes[toDelete]->destroy();
			m_meshes.erase(m_meshes.begin() + toDelete);
		}


		if (ImGui::Button("Add mesh")) {
			m_fileBrowser.Open();
			m_fileBrowser.SetPwd(ASSET_DIR);
		}
		if (m_fileBrowser.HasSelected()) {
			const std::string picked = m_fileBrowser.GetSelected().string();

			m_meshes.push_back(&instanciate<Mesh>(picked, false));

			m_fileBrowser.Close();
		}
	}


	ImGui::End();

	m_fileBrowser.Display();

}

