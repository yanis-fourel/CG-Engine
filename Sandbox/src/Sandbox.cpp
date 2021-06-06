#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <iostream>

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

#include "Sandbox.hpp"

#include "GameObjects/PongBall.hpp"
#include "GameObjects/InvisiblePlane.hpp"
#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/links/Spring.hpp"
#include "GameObjects/links/AnchorSpring.hpp"

#include "GameObjects/paddles/PlayerPaddle.hpp"
#include "GameObjects/paddles/AIPaddle.hpp"

#include "LevelCreator.hpp"

#include "AssetDir.hpp"



void Sandbox::start()
{
	getGame()->setAmbiantLight(CG::Color(0.8f, 0.8f, 0.8f, 1.f));

	resetSimulation();

	getGame()->setFrozen(false);
}

void Sandbox::resetSimulation()
{
	getGame()->setFrozen(true);
	getGame()->clearScene();

	getGame()->getObjectsOfTag<"simulation_object"_hs>([&](auto &obj) {
		obj.destroy();
		});

	// clear ^^^ vvv setup

	Level::create(*getGame());

	instanciate<FreeCameraManager>();

	auto ball = &instanciate<PongBall>(CG::Vector3(0, 0, 0), 0.5f);


	instanciate<PlayerPaddle>();
	instanciate<AIPaddle>();
}

void Sandbox::update(double deltatime)
{
	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();

	if (deltatime > 0)
		m_avgTimePerFrame.add(deltatime);

	float width = getGame()->getWindow().getSize().x;
	float height = 100;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::SetNextWindowBgAlpha(0.f);
	ImGui::Begin("Simulation", nullptr, ImGuiWindowFlags_NoDecoration);

	ImGui::Text("fps : %.1f (%.1fms)", 1 / getGame()->getRealDeltatime(), getGame()->getRealDeltatime() * 1000);
	ImGui::Text("Average time per frame : %.3fms", m_avgTimePerFrame.get() * 1000);

	ImGui::SetCursorPosX((width - 100) * 0.5f);
	if (ImGui::Button(getGame()->isFrozen() ? "Play" : "Pause", ImVec2(100, 0)))
		getGame()->setFrozen(!getGame()->isFrozen());

	ImGui::SameLine();
	if (ImGui::Button("Reset", ImVec2(50, 0))) {
		resetSimulation();
	}

	ImGui::End();

}
