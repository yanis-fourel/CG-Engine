#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <sstream>

#include <imgui.h>

#include <CG/utils/Random.hpp>
#include <CG/Color.hpp>
#include <CG/math/Vector3.hpp>
#include <CG/math/Utility.hpp>
#include <CG/prefabs/PointLight.hpp>
#include <CG/prefabs/Sphere.hpp>
#include <CG/prefabs/Plane.hpp>
#include <CG/ui/imfilebrowser.h>
#include <CG/physic/raycast/Raycast.hpp>

#include "CG/components/PointLight.hpp"
#include "CG/components/Rigidbody.hpp"
#include "CG/components/renderer/ShapeRenderer.hpp"
#include "CG/components/renderer/LineRenderer.hpp"

#include "CG/components/collider/PlaneCollider.hpp"

#include "PongGame.hpp"

#include "GameObjects/PongBall.hpp"
#include "GameObjects/InvisiblePlane.hpp"
#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/links/Spring.hpp"
#include "GameObjects/links/AnchorSpring.hpp"

#include "GameObjects/paddles/PlayerPaddle.hpp"
#include "GameObjects/paddles/AIPaddle.hpp"

#include "LevelCreator.hpp"

#include "AssetDir.hpp"



void PongGame::start()
{
	// Conserved default font
	ImGui::GetIO().Fonts->AddFontDefault();

	ImFontConfig cfg;
	cfg.SizePixels = 32.f;
	m_scoreFont = ImGui::GetIO().Fonts->AddFontDefault(&cfg);

	setAmbiantLight(CG::Color(0.8f, 0.8f, 0.8f, 1.f));

	resetSimulation();

	setFrozen(false);
}

void PongGame::resetSimulation()
{
	clearScene();

	// clear ^^^ vvv setup

	Level::create(*getGame());

	instanciate<FreeCameraManager>();

	auto ball = &instanciate<PongBall>(CG::Vector3(0, 0, 0), 0.5f);


	instanciate<PlayerPaddle>();
	instanciate<AIPaddle>();
}

void PongGame::onScore(Team goalTeam)
{
	spdlog::info("Goal for {}", goalTeam == Team::Player ? "AI" : "player");
	m_shouldReset = true;

	if (goalTeam == Team::Player)
		m_EnemiScore++;
	else
		m_playerScore++;
}

void PongGame::update(double deltatime)
{
	if (m_shouldReset) {
		resetSimulation();
		m_shouldReset = false;
	}

	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();

	if (deltatime > 0)
		m_avgTimePerFrame.add(deltatime);

	float width = getWindow().getSize().x;
	float height = 100;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::SetNextWindowBgAlpha(0.f);
	ImGui::Begin("Simulation", nullptr, ImGuiWindowFlags_NoDecoration);

	ImGui::Text("fps : %.1f (%.1fms)", 1 / getRealDeltatime(), getRealDeltatime() * 1000);
	ImGui::Text("Average time per frame : %.3fms", m_avgTimePerFrame.get() * 1000);

	ImGui::SetCursorPosX((width - 100) * 0.5f);
	ImGui::SetCursorPosY(10);

	if (ImGui::Button(isFrozen() ? "Play" : "Pause", ImVec2(100, 0))
		|| getInputManager().isKeyPressed(GLFW_KEY_SPACE))
		setFrozen(!isFrozen());

	ImGui::SameLine();
	if (ImGui::Button("Reset", ImVec2(50, 0))) {
		resetSimulation();
	}


	{
		ImGui::PushFont(m_scoreFont);

		// TODO: replace with std::format once it's implemented with MSVC
		auto text = (std::stringstream{} << "Player " << m_playerScore << " : " << m_EnemiScore << " Enemy").str();
		auto textSize = ImGui::CalcTextSize(text.c_str()).x;

		ImGui::SetCursorPosX((width - textSize) * 0.5f);
		ImGui::SetCursorPosY(50);

		ImGui::Text(text.c_str());
		ImGui::PopFont();
	}

	ImGui::End();
}
