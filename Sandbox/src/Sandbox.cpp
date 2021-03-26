#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <iostream>

#include <imgui.h>

#include <CG/Color.hpp>
#include <CG/math/Vector3.hpp>
#include <CG/prefabs/PointLight.hpp>
#include <CG/prefabs/Sphere.hpp>
#include <CG/ui/imfilebrowser.h>

#include "CG/components/PointLight.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/renderer/SphereRenderer.hpp"
#include "CG/components/renderer/CubeRenderer.hpp"

#include "Sandbox.hpp"

#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/Tile.hpp"
#include "GameObjects/Mesh.hpp"
#include "GameObjects/Grid.hpp"
#include "GameObjects/HomeworkBall.hpp"
#include "AssetDir.hpp"


void Sandbox::start()
{
	srand(time(nullptr)); // TODO: Engine random utilities

	instanciate<FreeCameraManager>();
	getGame()->setAmbiantLight(CG::Color(0.8f, 0.8f, 0.8f, 1.f));
	instanciate<Grid>(CG::Vector2(20, 20));
	m_pointLight = &instanciate<CG::prefabs::PointLight>(CG::Vector3{ 1, 5, 2 }, CG::Color::White());

	createAxis();
	resetSimulation();
}
void Sandbox::createAxis()
{
	constexpr auto axisThickness = 0.05f;
	constexpr auto axisLength = 100000.f;

	instanciate<CG::prefabs::Cube>(CG::Transform{ CG::Vector3(0, axisLength * 0.5f, 0), CG::Quaternion::identity(), CG::Vector3(axisThickness, axisLength, axisThickness) })
		.getComponent<CG::CubeRenderer>().setMaterial(CG::Material::RedPlastic());
	instanciate<CG::prefabs::Cube>(CG::Transform{ CG::Vector3(axisLength * 0.5f, 0, 0), CG::Quaternion::identity(), CG::Vector3(axisLength, axisThickness, axisThickness) })
		.getComponent<CG::CubeRenderer>().setMaterial(CG::Material::GreenPlastic());
	instanciate<CG::prefabs::Cube>(CG::Transform{ CG::Vector3(0, 0, axisLength * 0.5f), CG::Quaternion::identity(), CG::Vector3(axisThickness, axisThickness, axisLength) })
		.getComponent<CG::CubeRenderer>().setMaterial(CG::Material::BluePlastic());
}

void Sandbox::resetSimulation()
{
	getGame()->setFrozen(true);
	m_simulationTime = 0;


	for (auto &obj : m_simulationObjects)
		obj->destroy();
	m_simulationObjects.clear();

	// clear ^^^ vvv setup


	for (int i = 0; i < m_ballsCount; ++i)
		spawnBall();
}

void Sandbox::spawnBall()
{
#define RAND_0_1 (static_cast<float>(rand()) / RAND_MAX) 
#define RANDRANGE(x, y) ((x) + RAND_0_1 * ((y) - (x)))
	CG::Vector3 pos
	{
		RANDRANGE(-8, 8),
		RANDRANGE(1, 5),
		RANDRANGE(-8, 7),
	};

	auto &ball = instanciate<HomeworkBall>(pos, 0.1f, RANDRANGE(0.5f, 0.95f));
	m_simulationObjects.push_back(&ball);
}

void Sandbox::update(double deltatime)
{
	m_simulationTime += static_cast<float>(deltatime);

	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();

	//if (getInputManager().isMouseCaptured())
	//	return;

	float width = getGame()->getWindow().getSize().x;
	float height = 125;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::SetNextWindowBgAlpha(0.f);
	ImGui::Begin("Simulation", nullptr, ImGuiWindowFlags_NoDecoration);

	ImGui::Text("fps : %.1f (%.1fms)", 1 / getGame()->getRealDeltatime(), getGame()->getRealDeltatime());
	ImGui::Text("Simulation time : %.3fs", m_simulationTime);

	ImGui::SetCursorPosX((width - 100) * 0.5f);
	if (ImGui::Button(getGame()->isFrozen() ? "Play" : "Pause", ImVec2(100, 0)))
		getGame()->setFrozen(!getGame()->isFrozen());

	ImGui::SameLine();
	if (ImGui::Button("Reset", ImVec2(50, 0))) {
		resetSimulation();
	}

	static float asf = m_ballsCount;
	ImGui::SliderFloat("Balls count", &asf, 1, 1'000, "%.0f balls", ImGuiSliderFlags_Logarithmic );
	m_ballsCount = std::round(asf);

	ImGui::Text("[F1] to toggle free camera mode (WASDQE + mouse)");
	ImGui::Text("balls can't collide to each other. only to floor and invisible wall at x=9.5");

	ImGui::End();


	while (m_simulationObjects.size() > m_ballsCount) {
		m_simulationObjects.front()->destroy();
		m_simulationObjects.erase(m_simulationObjects.begin());
	}
	while (m_simulationObjects.size() < m_ballsCount)
		spawnBall();
}

