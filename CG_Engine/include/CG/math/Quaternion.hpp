#pragma once

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
	static Quaternion fromRotationAxis(Vector3 axis, float angle) noexcept
	{
		return glm::angleAxis(angle, static_cast<glm::vec3>(axis.normalized()));
	}

	constexpr operator glm::quat() const noexcept
	{
		return _quat;
	}

	Quaternion operator*(const Quaternion &other) const noexcept
	{
		return _quat * other._quat;
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