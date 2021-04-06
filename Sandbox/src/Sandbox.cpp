#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <iostream>

#include <imgui.h>

#include <CG/Color.hpp>
#include <CG/math/Vector3.hpp>
#include <CG/math/Utility.hpp>
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
#include "GameObjects/Grid.hpp"
#include "AssetDir.hpp"


void Sandbox::start()
{
	srand(static_cast<unsigned int>(time(nullptr))); // TODO: Engine random utilities

	instanciate<FreeCameraManager>();
	getGame()->setAmbiantLight(CG::Color(0.8f, 0.8f, 0.8f, 1.f));
	instanciate<Grid>(CG::Vector2(20, 20));
	m_pointLight = &instanciate<CG::prefabs::PointLight>(CG::Vector3{ 1, 5, 2 }, CG::Color::White());

	createAxis();
	resetSimulation();

	getGame()->setFrozen(false);
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


}

auto Sandbox::getRandomSpawnPoint() -> CG::Vector3 const
{
#define RAND_0_1 (static_cast<float>(rand()) / RAND_MAX) 
#define RANDRANGE(x, y) ((x) + RAND_0_1 * ((y) - (x)))

	return CG::Vector3{
		RANDRANGE(-8, 8),
		RANDRANGE(1, 5),
		RANDRANGE(-8, 7)
	};
}

void Sandbox::handleBallDragDrop()
{
	const auto &im = getInputManager();

	if (im.isMouseCaptured())
		return;


	const auto &screenPos = getWindow().pointToNormalized(im.getMousePosition());

	spdlog::info("Mouse pos : {}, {}", screenPos.x, screenPos.y);

	const auto ray = CG::getRayFromScreenPos(getCamera(), screenPos);

	spdlog::info("Ray : {}, {}, {}  ->   {}, {}, {}       mag : {}", ray.start.x, ray.start.y, ray.start.z, ray.finish.x, ray.finish.y, ray.finish.z, (ray.finish - ray.start).magnitude());

	//if (im.isKeyDown(GLFW_MOUSE_BUTTON_1)) {
	//	if (m_dragging) {
	//		
	//	}
	//}
}

void Sandbox::update(double deltatime)
{
	handleBallDragDrop();

	m_simulationTime += static_cast<float>(deltatime);

	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();

	//if (getInputManager().isMouseCaptured())
	//	return;

	float width = getGame()->getWindow().getSize().x;
	float height = 135;

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

	ImGui::Text("[F1] to toggle free camera mode (WASDQE + mouse)");

	ImGui::End();

}
