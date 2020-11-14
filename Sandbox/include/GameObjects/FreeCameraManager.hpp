#pragma once

#include "CG/GameObject.hpp"

class FreeCameraManager : public CG::AGameObject
{
public:
	FreeCameraManager();

	void start() override;
	void update(double deltatime);

private:
	double m_speed = 0.1;
	double m_rotSpeed = 0.1f;
};
