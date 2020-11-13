#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>

#include "CG/Camera.hpp"

void Camera::setPosition(const glm::vec3& pos)
{
	m_pos = pos;
}

void Camera::moveRelative(const glm::vec3& pos)
{
	auto abs = glm::vec4(pos.x, pos.y, pos.z, 1.f) * glm::lookAt(m_pos, m_pos + m_facing, m_up);

	moveAbs(static_cast<glm::vec3>(abs));
}

void Camera::moveAbs(const glm::vec3& pos)
{
	m_pos += pos;
}

void Camera::setUpDirection(const glm::vec3& vec)
{
	m_up = glm::normalize(vec);
}

void Camera::setFacingDirection(const glm::vec3& facing)
{
	m_facing = glm::normalize(facing);
}

void Camera::setFov(float fov)
{
	m_fov = fov;
}

void Camera::setAspectRatio(float aspect)
{
	m_aspectRatio = aspect;
}

void Camera::setRenderDistance(float distance)
{
	m_renderDistance = distance;
}

void Camera::rotateEuler(const glm::vec3& euler)
{
	auto rot = glm::eulerAngleYXZ(euler.y, euler.x, euler.z);

	m_facing = glm::vec4(m_facing.x, m_facing.y, m_facing.z, 1.f) * rot;
}


auto Camera::getViewProjMatrix() -> glm::mat4x4
{
	auto proj = glm::perspective(glm::radians(m_fov), m_aspectRatio, 0.1f, m_renderDistance);

	return proj * getViewMatrix();
}

void Camera::applyMouseMovement(float deltaYaw, float deltaPitch)
{
	glm::quat horizRot;
	horizRot = glm::angleAxis(deltaYaw, glm::vec3(0, 1, 0));

	glm::quat vertRot;
	vertRot = glm::angleAxis(deltaPitch, glm::cross(m_facing, m_up));

	glm::quat totalRot = horizRot * vertRot;

	m_facing = m_facing * totalRot;
}

auto Camera::getViewMatrix() -> glm::mat4x4
{
	return glm::lookAt(m_pos, m_pos + m_facing, m_up);
}
