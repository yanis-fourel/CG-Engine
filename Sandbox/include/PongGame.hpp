#pragma once

#include <vector>
#include <imgui.h>

#include "CG/Game.hpp"
#include "CG/Color.hpp"
#include "CG/math/Vector2.hpp"
#include "CG/math/Vector3.hpp"

#include <CG/ui/imfilebrowser.h>
#include <CG/prefabs/PointLight.hpp>
#include <CG/prefabs/Cube.hpp>
#include <CG/utils/Average.hpp>

#include "GameObjects/Goal.hpp"

class PongGame : public CG::AGame {
public:
	PongGame() : CG::AGame(CG::Vector2{ 1600, 900 }, "PongGame")
	{}

	void start() override;
	void update(double deltatime) override;

	void onScore(Team goalTeam);
private:
	void createAxis();
	void resetSimulation();

private:
	CG::Average<double> m_avgTimePerFrame;
	bool m_shouldReset = false;

	int m_playerScore = 0;
	int m_EnemiScore = 0;

	ImFont *m_scoreFont;
};