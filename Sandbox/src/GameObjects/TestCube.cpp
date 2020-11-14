#include "GameObjects/TestCube.hpp"

TestCube::TestCube()
{
	std::array<CG::Color, 8> colors = {
		CG::Color{1, 0, 0, 1},
		CG::Color{0, 1, 0, 1},
		CG::Color{0, 0, 1, 1},
		CG::Color{0, 0, 0, 1},
		CG::Color{1, 1, 0, 1},
		CG::Color{0, 1, 1, 1},
		CG::Color{1, 0, 1, 1},
		CG::Color{1, 1, 1, 1},
	};

	addComponent<CG::CubeRenderer>(colors);
}
