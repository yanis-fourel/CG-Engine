#pragma once

#include <vector>

#include "CG/Game.hpp"
#include "CG/Color.hpp"
#include "CG/Vector2.hpp"

class Sandbox : public CG::AGame {
public:
	Sandbox() : CG::AGame(CG::Vector2{1600, 900}, "Floor tile assignment")
	{}

	void start() override;
	void update(double deltatime) override;

private:
	void regenerateGrid();

private:
	bool m_shouldRegenerateGrid = true;

	std::vector<CG::Color> m_gridColors;
	int m_gridSize{};
	CG::Vector2 m_tileSize{};
};