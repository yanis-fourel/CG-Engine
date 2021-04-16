#pragma once

#include <CG/prefabs/Cube.hpp>
#include <CG/math/Vector3.hpp>

#include <cyclone/particle.h>


class WaterCube : public CG::prefabs::Cube
{
public:
	WaterCube(const CG::Vector3 &pos, float sideSize);

private:
	static constexpr float kHeight = 2;
};
