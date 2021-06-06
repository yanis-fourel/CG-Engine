#pragma once

#include "GameObjects/InvisiblePlane.hpp"

enum class Team {
	Player,
	Enemy
};

class Goal : public InvisiblePlane
{
public:
	Goal(Team team, float posZ);

	void onCollide(CG::GameObject &other) override;

private:
	Team m_team;
};
