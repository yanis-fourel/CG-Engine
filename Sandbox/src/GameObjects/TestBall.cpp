#include <CG/Material.hpp>
#include <CG/components/renderer/SphereRenderer.hpp>
#include <CG/components/Updateable.hpp>
#include <CG/components/Transform.hpp>

#include <CG/InputManager.hpp>

#include "GameObjects/TestBall.hpp"

TestBall::TestBall(const CG::Vector3 &pos, float radius) : CG::prefabs::Sphere(pos, radius)
{
	getComponent<CG::SphereRenderer>().setMaterial(CG::Material::Ruby());

	addComponent<CG::Updateable>([this](double d) {update(d); });
}

void TestBall::update(double deltatime)
{
	CG::Vector3 speed = CG::Vector3::Zero();

	if (InputManager->isKeyDown(GLFW_KEY_UP))
		speed.x += 1;
	if (InputManager->isKeyDown(GLFW_KEY_DOWN))
		speed.x -= 1;
	if (InputManager->isKeyDown(GLFW_KEY_LEFT))
		speed.z -= 1;
	if (InputManager->isKeyDown(GLFW_KEY_RIGHT))
		speed.z += 1;

	getComponent<CG::Transform>().position += speed * deltatime;
}
