#include <CG/components/renderer/CubeRenderer.hpp>
#include <CG/components/Transform.hpp>
#include <CG/components/Updateable.hpp>

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
	addComponent<CG::Transform>();
	addComponent<CG::Updateable>([this](double d) { update(d); });
}

void TestCube::update(double deltatime)
{
	CG::Vector3 vel = CG::Vector3::Zero();

	if (InputManager->isKeyDown(GLFW_KEY_I))
		vel.x += 1;
	if (InputManager->isKeyDown(GLFW_KEY_K))
		vel.x -= 1;
	if (InputManager->isKeyDown(GLFW_KEY_J))
		vel.y += 1;
	if (InputManager->isKeyDown(GLFW_KEY_L))
		vel.y -= 1;

	getComponent<CG::Transform>().position += vel * deltatime;
}