#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "CG/math/Utility.hpp"

CG::Ray CG::getRayFromScreenPos(const Camera &cam, const Vector2 &screenPosNorm)
{
	auto vp = cam.getViewProjMatrix();
	auto ivp = glm::inverse(vp);

	glm::vec4 normHomNearPoint(screenPosNorm.x, -screenPosNorm.y, -1, 1);
	glm::vec4 normHomFarPoint(screenPosNorm.x, -screenPosNorm.y, 1, 1);

	return CG::Ray{
		.start = ivp * normHomNearPoint * cam.kNearRenderDistance,
		.finish = ivp * normHomFarPoint * cam.getRenderDistance()
	};
}
