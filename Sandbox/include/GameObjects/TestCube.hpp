#pragma once

#include <CG/GameObject.hpp>

class TestCube : public CG::AGameObject
{
public:
	TestCube();

	void update(double deltatime);
};
