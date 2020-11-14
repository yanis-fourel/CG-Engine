#include "Sandbox.hpp"
#include "imgui.h"

#include "GameObjects/FreeCameraManager.hpp"
#include "GameObjects/Tile.hpp"
#include "GameObjects/TestCube.hpp"

#include <CG/Color.hpp>
#include <CG/Vector3.hpp>

void Sandbox::start()
{
	instanciate<FreeCameraManager>();
	//instanciate<TestCube>();

	const std::vector<CG::Color> kColors = {
		CG::Color{0.7f, 0.7f, 0.7f, 1.f},
		CG::Color{0.3f, 0.3f, 0.3f, 1.f},
	};

	constexpr std::size_t kGridSize = 10;

	constexpr CG::Vector3 kTileScale{ 1, 1, 1 };

	for (std::size_t x = 0; x < kGridSize; ++x)
		for (std::size_t z = 0; z < kGridSize; ++z)
			instanciate<Tile>(CG::Vector3{x * kTileScale.x, 0, z * kTileScale.z}, kTileScale, kColors[(x + z) % kColors.size()]);


	//CG::Vector3 pos = CG::Vector3::Zero();
	//CG::Vector3 scale = CG::Vector3::One();
	//CG::Color color = CG::Color::Red();

	//instanciate<Tile>(pos, scale, color);
}

void Sandbox::update(double deltatime)
{
	if (getInputManager().isKeyDown(GLFW_KEY_ESCAPE))
		getWindow().close();
}
