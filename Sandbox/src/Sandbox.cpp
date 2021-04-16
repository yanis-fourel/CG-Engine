#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <iostream>

#include <imgui.h>

#include <CG/Color.hpp>
#include <CG/math/Vector3.hpp>
#include <CG/math/Utility.hpp>
#include <CG/prefabs/PointLight.hpp>
#include <CG/prefabs/Sphere.hpp>
#include <CG/prefabs/Plane.hpp>
#include <CG/ui/imfilebrowser.h>
#include <CG/physic/Raycast.hpp>

#include "CG/components/PointLight.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/renderer/ShapeRenderer.hpp"
#include "CG/components/renderer/LineRenderer.hpp"

#include "CG/components/collider/PlaneCollider.hpp"

#include "Sandbox.hpp"

#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/Tile.hpp"
#include "GameObjects/TestBall.hpp"
#include "GameObjects/Spring.hpp"
#include "GameObjects/AnchorSpring.hpp"
#include "GameObjects/WaterCube.hpp"
#include "AssetDir.hpp"


void Sandbox::start()
{
	srand(static_cast<unsigned int>(time(nullptr))); // TODO: Engine random utilities

	instanciate<FreeCameraManager>();
	getGame()->setAmbiantLight(CG::Color(0.8f, 0.8f, 0.8f, 1.f));
	m_pointLight = &instanciate<CG::prefabs::PointLight>(CG::Vector3{ 1, 5, 2 }, CG::Color::White());

	createGrid(CG::Vector2(20, 20));
	createAxis();
	resetSimulation();
}

void Sandbox::createGrid(const CG::Vector2 &size)
{
	float height = 0.f;

	for (int x = static_cast<int>(size.x * -.5); x < size.x * 0.5; ++x)
		for (int y = static_cast<int>(size.y * -.5); y < size.y * 0.5; ++y)
			instanciate<Tile>(
				CG::Vector3(x + 0.5f, height, y + 0.5f),
				CG::Vector2::One(),
				(x + y) % 2 ? CG::material::Solid::BlackRubber() : CG::material::Solid::WhiteRubber()
				);
}

void Sandbox::createAxis()
{
	constexpr auto axisLength = 100000.f;

	instanciate<CG::GameObject>().addComponent<CG::LineRenderer>(CG::Vector3::Zero(), CG::Vector3(axisLength, 0, 0), CG::material::Line {CG::Color::Red()});
	instanciate<CG::GameObject>().addComponent<CG::LineRenderer>(CG::Vector3::Zero(), CG::Vector3(0, axisLength, 0), CG::material::Line {CG::Color::Green()});
	instanciate<CG::GameObject>().addComponent<CG::LineRenderer>(CG::Vector3::Zero(), CG::Vector3(0, 0, axisLength), CG::material::Line {CG::Color::Blue()});

	//instanciate<CG::prefabs::Cube>(CG::Transform{ CG::Vector3(0, axisLength * 0.5f, 0), CG::Quaternion::identity(), CG::Vector3(axisThickness, axisLength, axisThickness) })
	//	.getComponent<CG::ShapeRenderer>().material = std::make_unique<CG::material::Solid>(CG::material::Solid::RedPlastic());
	//instanciate<CG::prefabs::Cube>(CG::Transform{ CG::Vector3(axisLength * 0.5f, 0, 0), CG::Quaternion::identity(), CG::Vector3(axisLength, axisThickness, axisThickness) })
	//	.getComponent<CG::ShapeRenderer>().material = std::make_unique<CG::material::Solid>(CG::material::Solid::GreenPlastic());
	//instanciate<CG::prefabs::Cube>(CG::Transform{ CG::Vector3(0, 0, axisLength * 0.5f), CG::Quaternion::identity(), CG::Vector3(axisThickness, axisThickness, axisLength) })
	//	.getComponent<CG::ShapeRenderer>().material = std::make_unique<CG::material::Solid>(CG::material::Solid::BluePlastic());
}

void Sandbox::resetSimulation()
{
	getGame()->setFrozen(true);
	m_simulationTime = 0;


	getGame()->getObjectsOfTag<"simulation_object"_hs>([&](auto &obj) {
		obj.destroy();
		});

	// clear ^^^ vvv setup

	std::vector<CG::material::Solid> materials = {
		CG::material::Solid::Default(),
		CG::material::Solid::Emerald(),
		CG::material::Solid::Jade(),
		CG::material::Solid::Obsidian(),
		CG::material::Solid::Pearl(),
		CG::material::Solid::Ruby(),
		CG::material::Solid::Turquoise(),
		CG::material::Solid::Brass(),
		CG::material::Solid::Bronze(),
		CG::material::Solid::Chrome(),
		CG::material::Solid::Copper(),
		CG::material::Solid::Gold(),
		CG::material::Solid::Silver(),
		CG::material::Solid::BlackPlastic(),
		CG::material::Solid::WhitePlastic(),
		CG::material::Solid::CyanPlastic(),
		CG::material::Solid::GreenPlastic(),
		CG::material::Solid::RedPlastic(),
		CG::material::Solid::YellowPlastic(),
		CG::material::Solid::BluePlastic(),
		CG::material::Solid::BlackRubber(),
		CG::material::Solid::CyanRubber(),
		CG::material::Solid::GreenRubber(),
		CG::material::Solid::RedRubber(),
		CG::material::Solid::WhiteRubber(),
		CG::material::Solid::YellowRubber(),
		CG::material::Solid::BlueRubber(),
	};

	std::vector<CG::GameObject *> balls;

	constexpr auto ballCount = 10;
	for (int i = 0; i < ballCount; ++i) {
		auto &obj = instanciate<TestBall>(getRandomSpawnPoint(), 0.5f, materials[i % materials.size()]);

		for (auto &prev : balls)
			instanciate<Spring>(obj, *prev, 1.f, 3.f);

		balls.push_back(&obj);
	}

	instanciate<WaterCube>(CG::Vector3(0, 1, 0), 20);
	auto &obj = instanciate<TestBall>(getRandomSpawnPoint(), 0.5f, materials[std::rand() % materials.size()]);
	instanciate<AnchorSpring>(CG::Vector3(0, 3, 0), obj, 5.f, 1.f);
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
	constexpr auto kBind = GLFW_MOUSE_BUTTON_LEFT;

	const auto &im = getInputManager();

	if (im.isMouseCaptured())
		return;

	if (!m_dragging) {
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
			const auto &screenPos = getWindow().pointToNormalized(im.getMousePosition());
			const auto ray = CG::getRayFromScreenPos(getCamera(), screenPos);
			const auto castResult = CG::castRaycast(*getGame(), ray);

			if (castResult.hit && castResult.object->hasTag<"simulation_object"_hs>())
				m_dragging = castResult.object;
		}

	}
	else {
		if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
			CG::Transform planTransform{ m_dragging->getComponent<CG::Transform>().position, CG::Quaternion::fromEuler(0, 3.1415 * 0.5f, 0), CG::Vector3::One() };

			if (im.isKeyDown(GLFW_KEY_LEFT_CONTROL))
				planTransform.rotation = CG::Quaternion::identity();

			const auto &screenPos = getWindow().pointToNormalized(im.getMousePosition());
			const auto ray = CG::getRayFromScreenPos(getCamera(), screenPos);

			auto castResult = CG::castRaycastOn(CG::PlaneCollider{}, planTransform, ray);
			if (!castResult) {
				planTransform.rotation *= CG::Quaternion::fromEuler(180, 0, 0);
				castResult = CG::castRaycastOn(CG::PlaneCollider{}, planTransform, ray);
			}

			if (castResult)
				m_dragging->getComponent<CG::Transform>().position = *castResult;
		}

		if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
			m_dragging = nullptr;
	}

}

void Sandbox::update(double deltatime)
{
	if (getGame()->isFrozen())
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

	ImGui::Text("fps : %.1f (%.1fms)", 1 / getGame()->getRealDeltatime(), getGame()->getRealDeltatime() * 1000);
	ImGui::Text("Simulation time : %.3fs", m_simulationTime);

	ImGui::SetCursorPosX((width - 100) * 0.5f);
	if (ImGui::Button(getGame()->isFrozen() ? "Play" : "Pause", ImVec2(100, 0)))
		getGame()->setFrozen(!getGame()->isFrozen());

	ImGui::SameLine();
	if (ImGui::Button("Reset", ImVec2(50, 0))) {
		resetSimulation();
	}

	ImGui::Text("[F1] to toggle free camera mode (WASDQE + mouse)");
	ImGui::Text("You can grab the ball with the mouse, drag it around with left click on the XZ axis, or XY axis if you hold control");

	ImGui::End();

}
