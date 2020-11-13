#pragma once

#include "CG/Game.hpp"

class Sandbox : public CG::AGame {
public:
	void start() override;
	void update(double deltatime) override;
};