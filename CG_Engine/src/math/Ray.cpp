#include "CG/math/Ray.hpp"

auto CG::Ray::length() const noexcept -> float
{
	return (finish - start).magnitude();
}

auto CG::Ray::direction() const noexcept -> Vector3
{
	return (finish - start) / length();
}