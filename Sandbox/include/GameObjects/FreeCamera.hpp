#pragma once

#include "CG/GameObject.hpp"

class FreeCamera : public CG::AGameObject
{
public:
	FreeCamera();

	void start() override;
	void update(double deltatime);

private:
	double m_speed = 0.1;
	double m_rotSpeed = 0.1f;
};
