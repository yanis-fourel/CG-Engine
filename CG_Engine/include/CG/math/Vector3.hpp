#pragma once

#include <glm/vec3.hpp>
#include <cyclone/core.h>

namespace CG {

struct Vector3
{
	using value_type = float;

	value_type x, y, z;

	Vector3() = default;
	constexpr Vector3(value_type x, value_type y, value_type z) noexcept : x(x), y(y), z(z)
	{}

	constexpr Vector3(const glm::vec3 &vec) noexcept
		: x(static_cast<value_type>(vec.x)),
		y(static_cast<value_type>(vec.y)),
		z(static_cast<value_type>(vec.z))
	{}
	constexpr Vector3(const cyclone::Vector3 &vec) noexcept
		: x(static_cast<value_type>(vec.x)),
		y(static_cast<value_type>(vec.y)),
		z(static_cast<value_type>(vec.z))
	{}

	constexpr Vector3 &operator=(const glm::vec3 &vec) noexcept
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	constexpr operator glm::vec3() const noexcept
	{
		return glm::vec3{ x, y, z };
	}

	operator cyclone::Vector3() const noexcept
	{
		return cyclone::Vector3{ x, y, z };
	}



	double magnitude() const noexcept
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3 normalized() const noexcept
	{
		double m = magnitude();
		return {
			static_cast<value_type>(x / m),
			static_cast<value_type>(y / m),
			static_cast<value_type>(z / m)
		};
	}

	constexpr Vector3 operator -() const noexcept
	{
		return Vector3{ -x, -y, -z };
	}

	template <typename T>
	constexpr Vector3 operator*(T fact) const noexcept
	{
		return {
			x * static_cast<value_type>(fact),
			y * static_cast<value_type>(fact),
			z * static_cast<value_type>(fact)
		};
	}

	Vector3 operator+(const Vector3 &other) const noexcept
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	Vector3 operator-(const Vector3 &other) const noexcept
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	Vector3 &operator+=(const Vector3 &other)
	{
		*this = *this + other;
		return *this;
	}

	Vector3 &operator-=(const Vector3 &other)
	{
		*this = *this - other;
		return *this;
	}



	static constexpr Vector3 Zero() { return { 0, 0, 0 }; }
	static constexpr Vector3 One() { return { 1, 1, 1 }; }
	static constexpr Vector3 Up() { return { 0, 1, 0 }; }
	static constexpr Vector3 Down() { return -Up(); }
	static constexpr Vector3 Forward() { return { 0, 0, -1 }; }
	static constexpr Vector3 Backward() { return -Forward(); }
	static constexpr Vector3 Right() { return { 1, 0, 0 }; }
	static constexpr Vector3 Left() { return -Right(); }
};

}