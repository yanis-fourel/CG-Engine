#pragma once

#include <concepts>

#include "math/Vector3.hpp"

namespace CG {

// Values RGBA each in range [0, 1]
struct Color
{
	using value_type = float;

	value_type r, g, b, a;

	Color() = default;
	constexpr Color(value_type r, value_type g, value_type b, value_type a = 1) noexcept : r(r), g(g), b(b), a(a)
	{}

	constexpr Vector3 toVec3() const noexcept { return { r, g, b }; }

	static constexpr Color Transparent() { return { 1, 1, 1, 0 }; }
	static constexpr Color White() { return { 1, 1, 1, 1 }; }
	static constexpr Color Black() { return { 0, 0, 0, 1 }; }
	static constexpr Color Grey() { return { 0.5, 0.5, 0.5, 1 }; }

	static constexpr Color Red() { return { 1, 0, 0, 1 }; }
	static constexpr Color Green() { return { 0, 1, 0, 1 }; }
	static constexpr Color Blue() { return { 0, 0, 1, 1 }; }

	static constexpr Color Cyan() { return { 0, 1, 1, 1 }; }
	static constexpr Color Yellow() { return { 1, 0, 1, 1 }; }
	static constexpr Color Magenta() { return { 1, 1, 0, 1 }; }

};


inline Color lerp(const Color &a, const Color &b, Color::value_type val)
{
	return Color {
		std::lerp(a.r, b.r, val),
		std::lerp(a.g, b.g, val),
		std::lerp(a.b, b.b, val),
		std::lerp(a.a, b.a, val),
	};
}

}
