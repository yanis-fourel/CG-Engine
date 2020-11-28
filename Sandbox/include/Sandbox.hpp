#pragma once

#include <vector>

#include "CG/Game.hpp"
#include "CG/Color.hpp"
#include "CG/Vector2.hpp"

class Sandbox : public CG::AGame {
public:
	Sandbox() : CG::AGame(CG::Vector2{1600, 900}, "Sandbox")
	{}

	void start() override;
	void update(double deltatime) override;

private:

};