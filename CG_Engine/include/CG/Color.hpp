#pragma once

#include "Vector3.hpp"

namespace CG {

struct Color
{
	using value_type = float;

	value_type r, g, b, a;

	constexpr Vector3 toVec3() const noexcept { return { r, g, b }; }

	static constexpr Color Transparent() { return { 1, 1, 1, 0 }; }
	static constexpr Color White() { return { 1, 1, 1, 1 }; }
	static constexpr Color Black() { return { 0, 0, 0, 1 }; }

	static constexpr Color Red() { return { 1, 0, 0, 1 }; }
	static constexpr Color Green() { return { 0, 1, 0, 1 }; }
	static constexpr Color Blue() { return { 0, 0, 1, 1 }; }

	static constexpr Color Cyan() { return { 0, 1, 1, 1 }; }
	static constexpr Color Yellow() { return { 1, 0, 1, 1 }; }
	static constexpr Color Magenta() { return { 1, 1, 0, 1 }; }

};

}
