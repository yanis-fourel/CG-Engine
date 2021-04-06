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

	[[nodiscard]] auto getViewMatrix()const noexcept ->glm::mat4x4;
	[[nodiscard]] auto getViewProjMatrix()const noexcept ->glm::mat4x4;
	[[nodiscard]] auto getPosition() const noexcept -> const glm::vec3 &{ return m_pos; }
	[[nodiscard]] auto getFacing() const noexcept -> const glm::vec3 &{ return m_facing; }
	[[nodiscard]] auto getRenderDistance() const noexcept -> float { return m_renderDistance; }

	void applyMouseMovement(float deltaYaw, float deltaPitch);

public:
	static constexpr float kNearRenderDistance = 0.01f;

private:
	glm::vec3 m_pos = { 0, 0, 0 };
	glm::vec3 m_facing = { 0, 0, -1 };
	glm::vec3 m_up = { 0, 1, 0 };

	float m_fov = 45; // Degree
	float m_aspectRatio = 16.f / 9.f; // Horizontal
	float m_renderDistance = 100;
};
}
