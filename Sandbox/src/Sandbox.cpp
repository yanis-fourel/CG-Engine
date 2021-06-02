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

#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/PongBall.hpp"
#include "GameObjects/links/Spring.hpp"
#include "GameObjects/links/AnchorSpring.hpp"
#include "AssetDir.hpp"



void Sandbox::start()
{
	instanciate<FreeCameraManager>();
	getGame()->setAmbiantLight(CG::Color(0.8f, 0.8f, 0.8f, 1.f));
	m_pointLight = &instanciate<CG::prefabs::PointLight>(CG::Vector3{ 0, 50, 0 }, CG::Color::White());

	createAxis();
	resetSimulation();
}

void Sandbox::createAxis()
{
	constexpr auto axisLength = 100000.f;
	constexpr auto axisHeight = 0.0;

	instanciate<CG::GameObject>().addComponent<CG::LineRenderer>(CG::Vector3(0, axisHeight, 0), CG::Vector3(axisLength, axisHeight, 0), CG::material::Line{ CG::Color::Red() });
	instanciate<CG::GameObject>().addComponent<CG::LineRenderer>(CG::Vector3(0, axisHeight, 0), CG::Vector3(0, axisLength, 0), CG::material::Line{ CG::Color::Green() });
	instanciate<CG::GameObject>().addComponent<CG::LineRenderer>(CG::Vector3(0, axisHeight, 0), CG::Vector3(0, axisHeight, axisLength), CG::material::Line{ CG::Color::Blue() });
}

void Sandbox::resetSimulation()
{
	getGame()->setFrozen(true);
	m_simulationTime = 0;


	getGame()->getObjectsOfTag<"simulation_object"_hs>([&](auto &obj) {
		obj.destroy();
		});

	// clear ^^^ vvv setup

	//createBridge(*getGame());

		auto obj = &instanciate<TestBall>(getRandomSpawnPoint(), 0.5f);
	//std::vector<CG::GameObject *> objs;

	//for (int i = 0; i < 50; i++) {

	//	for (auto &o : objs)
	//		instanciate<Spring>(*obj, *o, 5, 5);

	//	objs.push_back(obj);
	//}
}

auto Sandbox::getRandomSpawnPoint() -> CG::Vector3 const
{
	return CG::Vector3{
		CG::RandomRange<float>(-8, 8),
		CG::RandomRange<float>(1, 5),
		CG::RandomRange<float>(-8, 7)
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
			CG::Transform planTransform{ m_dragging->getComponent<CG::Transform>().position, CG::Quaternion::identity(), CG::Vector3(9999, 0, 9999) };

			if (im.isKeyDown(GLFW_KEY_LEFT_CONTROL))
				planTransform.rotation = CG::Quaternion::fromLookDirection(CG::Vector3::Up(), CG::Vector3::Right());

			// TODO: Still some debug to do here
			//instanciate<CG::prefabs::Plane>(planTransform).getComponent<CG::ShapeRenderer>().material = std::make_unique<CG::material::Solid>(CG::material::Solid::Chrome());

			const auto &screenPos = getWindow().pointToNormalized(im.getMousePosition());
			const auto ray = CG::getRayFromScreenPos(getCamera(), screenPos);

			auto castResult = CG::castRaycastOn(CG::PlaneCollider{}, planTransform, ray);
			if (!castResult) {
				planTransform.rotation *= CG::Quaternion::fromEuler(0, std::numbers::pi, 0);
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
	handleBallDragDrop();

	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();

	if (deltatime > 0) {
		m_avgTimePerFrame.add(deltatime);
		m_simulationTime += static_cast<float>(deltatime);
	}

	//if (getInputManager().isMouseCaptured())
	//	return;

	float width = getGame()->getWindow().getSize().x;
	float height = 200;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(width, height));
	ImGui::SetNextWindowBgAlpha(0.f);
	ImGui::Begin("Simulation", nullptr, ImGuiWindowFlags_NoDecoration);

	ImGui::Text("fps : %.1f (%.1fms)", 1 / getGame()->getRealDeltatime(), getGame()->getRealDeltatime() * 1000);
	ImGui::Text("Simulation time : %.3fs", m_simulationTime);
	ImGui::Text("Average time per frame : %.3fms", m_avgTimePerFrame.get() * 1000);

	ImGui::SetCursorPosX((width - 100) * 0.5f);
	if (ImGui::Button(getGame()->isFrozen() ? "Play" : "Pause", ImVec2(100, 0)))
		getGame()->setFrozen(!getGame()->isFrozen());

	ImGui::SameLine();
	if (ImGui::Button("Reset", ImVec2(50, 0))) {
		resetSimulation();
	}

	ImGui::SetCursorPosX((width - 1200) * 0.5f);
	if (ImGui::Button("reset")) {
		m_simulationSpeed = 1;
		getGame()->setGlobalTimeFactor(m_simulationSpeed);
	}
	ImGui::SameLine();
	if (ImGui::SliderFloat("Simulation speed", &m_simulationSpeed, 0.01f, 10))
		getGame()->setGlobalTimeFactor(m_simulationSpeed);

	{ // Freeze in x ticks
		ImGui::SetCursorPosX((width - 100) * 0.5f);

		auto buttonEnabled = getGame()->isFrozen();
		if (!buttonEnabled)
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);

		auto local_freezeIn = 0;

		local_freezeIn += ImGui::Button("1 tick"); ImGui::SameLine();
		local_freezeIn += 2 * ImGui::Button("2"); ImGui::SameLine();
		local_freezeIn += 5 * ImGui::Button("5"); ImGui::SameLine();
		local_freezeIn += 30 * ImGui::Button("30");

		if (local_freezeIn && buttonEnabled) {
			getGame()->setFrozen(false);
			m_freezeInXTicks = local_freezeIn + 1;
		}

		if (!buttonEnabled)
			ImGui::PopStyleVar();

		if (m_freezeInXTicks > 0 && --m_freezeInXTicks == 0)
			getGame()->setFrozen(true);
	}

	{
		static bool pauseAtEnabled = false;

		ImGui::Text("Pause at t=");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(150);
		pauseAtEnabled |= ImGui::InputDouble("##pauseAtInput", &m_pauseAtSimulationTime, 0.0, 0.0, "%.2f");
		ImGui::SameLine();
		ImGui::Checkbox("##pauseAtInput_enabled", &pauseAtEnabled);

		if (pauseAtEnabled && m_simulationTime >= m_pauseAtSimulationTime) {
			getGame()->setFrozen(true);
			pauseAtEnabled = false;
		}
	}

	ImGui::Text("[F1] to toggle free camera mode (WASDQE + mouse)");
	ImGui::Text("You can grab the ball with the mouse, drag it around with left click on the XZ axis, or XY axis if you hold control");

	ImGui::End();

}
