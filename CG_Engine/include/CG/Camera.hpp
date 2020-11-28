#pragma once

#include <glm/mat4x4.hpp>

namespace CG {
class Camera
{
public:
	Camera() = default;

	void setPosition(const glm::vec3 &pos);
	void moveRelative(const glm::vec3 &pos);
	void moveAbs(const glm::vec3 &pos);

	void setUpDirection(const glm::vec3 &vec);
	void setFacingDirection(const glm::vec3 &pos);
	void setFov(float fov);
	void setAspectRatio(float aspect);
	void setRenderDistance(float distance);

	auto getViewMatrix()const noexcept ->glm::mat4x4;
	auto getViewProjMatrix()const noexcept ->glm::mat4x4;
	auto getPosition() const noexcept -> const glm::vec3 &{ return m_pos; }
	auto getFacing() const noexcept -> const glm::vec3 &{ return m_facing; }

	void applyMouseMovement(float deltaYaw, float deltaPitch);

private:
	glm::vec3 m_pos = { 0, 0, 0 };
	glm::vec3 m_facing = { 0, 0, -1 };
	glm::vec3 m_up = { 0, 1, 0 };

	float m_fov = 45; // Degree
	float m_aspectRatio = 16 / 9; // Horizontal
	float m_renderDistance = 1;
};
}
