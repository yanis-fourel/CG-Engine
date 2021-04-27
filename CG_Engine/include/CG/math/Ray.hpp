#pragma once

#include "Vector3.hpp"

namespace CG {

struct Ray {
	Vector3 start;
	Vector3 finish;

	[[nodiscard]] auto length() const noexcept -> double;
	[[nodiscard]] auto direction() const noexcept -> Vector3;
};

}
