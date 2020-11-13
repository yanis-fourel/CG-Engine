#pragma once

#include "CG/GameObject.hpp"

class FreeCamera : public CG::AGameObject
{
public:
	FreeCamera();

	void start() override;
	void update(double deltatime);

private:
	float m_speed = 0.1;
	float m_rotSpeed = 0.1f;
};
