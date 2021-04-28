#pragma once

#include <numbers>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Vector3.hpp"

namespace CG {

class Quaternion
{
public:
	Quaternion() = default;
	Quaternion(const glm::quat &quat) : _quat(quat)
	{}

	static Quaternion identity() noexcept
	{
		return Quaternion(glm::quat_identity<float, glm::packed_highp>());
	}

	// Angles in radian
	static Quaternion fromEuler(float yaw, float pitch, float roll) noexcept
	{
		return glm::quat(glm::vec3(pitch, yaw, roll));
	}

	// Angles in radian
	static Quaternion fromRotationAxis(const Vector3 &axis, float angle) noexcept
	{
		return glm::angleAxis(angle, static_cast<glm::vec3>(axis.normalized()));
	}

	static Quaternion fromLookDirection(const Vector3 &lookDirection, const Vector3 &upDirection = Vector3::Up()) noexcept
	{
		return glm::quatLookAt(static_cast<glm::vec3>(lookDirection), static_cast<glm::vec3>(upDirection));
	}

	static Quaternion inverse(const Quaternion &quat) noexcept
	{
		return glm::inverse(static_cast<glm::quat>(quat));
	}

	constexpr operator glm::quat() const noexcept
	{
		return _quat;
	}

	Quaternion operator*(const Quaternion &other) const noexcept
	{
		return _quat * other._quat;
	}

	Vector3 operator*(const Vector3 &vec) const noexcept
	{
		return static_cast<glm::vec3>(vec) * _quat;
	}

	Quaternion &operator*=(const Quaternion &other) noexcept
	{
		*this = *this * other;
		return *this;
	}

private:
	glm::quat _quat;
};

}