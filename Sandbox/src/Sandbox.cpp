#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <iostream>

#include <imgui.h>

#include <CG/Color.hpp>
#include <CG/Vector3.hpp>
#include <CG/prefabs/PointLight.hpp>
#include <CG/prefabs/Sphere.hpp>
#include <CG/ui/imfilebrowser.h>

#include "CG/components/PointLight.hpp"
#include "CG/components/Transform.hpp"

#include "Sandbox.hpp"

#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/Tile.hpp"
#include "GameObjects/Mesh.hpp"
#include "GameObjects/Grid.hpp"
#include "AssetDir.hpp"


void Sandbox::start()
{
	getGame()->setAmbiantLight(CG::Color(0.2f, 0.2f, 0.2f, 1.f));
	m_pointLight = &instanciate<CG::prefabs::PointLight>(CG::Vector3{ 1, 5, 2 }, CG::Color::White());

	instanciate<FreeCameraManager>();
	instanciate<Grid>(CG::Vector2(20, 20));
	instanciate<CG::prefabs::Sphere>(CG::Vector3::Up() * 2, 1, CG::Color::Red());
}

void Sandbox::update(double deltatime)
{
	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();

	//if (getInputManager().isMouseCaptured())
	//	return;
}

