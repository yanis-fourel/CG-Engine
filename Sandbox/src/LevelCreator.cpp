#include <CG/prefabs/PointLight.hpp>
#include <CG/components/renderer/LineRenderer.hpp>

#include "LevelCreator.hpp"
#include "GameObjects/InvisiblePlane.hpp"

namespace Level {


CG::Vector3 topLeft(double z) { return CG::Vector3(kWidth * -0.5, kHeight * 0.5, z); }
CG::Vector3 topRight(double z) { return CG::Vector3(kWidth * 0.5, kHeight * 0.5, z); }
CG::Vector3 bottomRight(double z) { return CG::Vector3(kWidth * 0.5, -kHeight * 0.5, z); }
CG::Vector3 bottomLeft(double z) { return CG::Vector3(kWidth * -0.5, -kHeight * 0.5, z); }


void setupCamera(CG::Camera &cam)
{
	{
		auto x = 0;
		auto y = 0;
		auto z = 1.2 * (kDepth * 0.5);

		cam.setPosition(glm::vec3(x, y, z));
	}

	cam.setFacingDirection(CG::Vector3::Forward());
	cam.setUpDirection(glm::vec3(0, 1, 0));
	cam.setFov(90);
	cam.setAspectRatio(16.f / 9);
	cam.setRenderDistance(99999);
}

void addRay(CG::AGame &game, const CG::Vector3 &from, const CG::Vector3 &to, const CG::Color &color)
{
	game.instanciate<CG::GameObject>().addComponent<CG::LineRenderer>(from, to, CG::material::Line(color));
}

void addRing(CG::AGame &game, float posZ, const CG::Color &color)
{
	addRay(game, topLeft(posZ), topRight(posZ), color);
	addRay(game, topRight(posZ), bottomRight(posZ), color);
	addRay(game, bottomRight(posZ), bottomLeft(posZ), color);
	addRay(game, bottomLeft(posZ), topLeft(posZ), color);
}

void create(CG::AGame &game)
{
	game.instanciate<InvisiblePlane>(CG::Vector3(0, -0.5 * kHeight, 0), CG::Quaternion::identity());
	game.instanciate<InvisiblePlane>(CG::Vector3(0, +0.5 * kHeight, 0), CG::Quaternion::fromEuler(0, 0, std::numbers::pi));
	game.instanciate<InvisiblePlane>(CG::Vector3(-0.5 * kWidth, 0, 0), CG::Quaternion::fromEuler(0, 0, +0.5 * std::numbers::pi));
	game.instanciate<InvisiblePlane>(CG::Vector3(+0.5 * kWidth, 0, 0), CG::Quaternion::fromEuler(0, 0, -0.5 * std::numbers::pi));



	setupCamera(game.getCamera());
	game.getInputManager().setMouseCapture(false);

	game.instanciate<CG::prefabs::PointLight>(CG::Vector3{ 0, 50, 0 }, CG::Color::White());


	addRing(game, kDepth * 0.5, kFrontEdgesColor);
	addRing(game, kDepth * -0.5, kBackEdgesColor);

	for (int i = 0; i < kMiddleRingsCount; i++)
		addRing(game, std::lerp(kDepth * 0.5f, kDepth * -0.5f, static_cast<double>(i + 1) / (kMiddleRingsCount + 1)), kMiddleEdgesColor);

	addRay(game, topLeft(kDepth * 0.5), topLeft(kDepth * -0.5), kFourEdgesColor);
	addRay(game, topRight(kDepth * 0.5), topRight(kDepth * -0.5), kFourEdgesColor);
	addRay(game, bottomLeft(kDepth * 0.5), bottomLeft(kDepth * -0.5), kFourEdgesColor);
	addRay(game, bottomRight(kDepth * 0.5), bottomRight(kDepth * -0.5), kFourEdgesColor);
}

}
