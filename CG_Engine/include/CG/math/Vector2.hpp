#pragma once

#include <glm/vec2.hpp>

namespace CG {

struct Vector2
{
	using value_type = float;

	value_type x, y;

	Vector2() = default;
	constexpr Vector2(value_type x, value_type y) noexcept : x(x), y(y)
	{}

	constexpr operator glm::vec2() const noexcept
	{
		return glm::vec2(x, y);
	}

	template <typename T>
	constexpr Vector2 operator*(T fact) const noexcept
	{
		return {
			x * static_cast<value_type>(fact),
			y * static_cast<value_type>(fact)
		};
	}

	Vector2 operator+(const Vector2 &other) const noexcept
	{
		return { x + other.x, y + other.y };
	}

	Vector2 operator-(const Vector2 &other) const noexcept
	{
		return { x - other.x, y - other.y };
	}

	Vector2 operator*(const Vector2 &other) const noexcept
	{
		return { x * other.x, y * other.y };
	}

	Vector2 operator/(const Vector2 &other) const noexcept
	{
		return { x / other.x, y / other.y };
	}

	Vector2 &operator+=(const Vector2 &other)
	{
		*this = *this + other;
		return *this;
	}

	Vector2 &operator-=(const Vector2 &other)
	{
		*this = *this - other;
		return *this;
	}

	Vector2 &operator*=(const Vector2 &other)
	{
		*this = *this * other;
		return *this;
	}

	Vector2 &operator/=(const Vector2 &other)
	{
		*this = *this / other;
		return *this;
	}


	static constexpr Vector2 Zero() { return { 0, 0 }; }
	static constexpr Vector2 One() { return { 1, 1 }; }
};

}
