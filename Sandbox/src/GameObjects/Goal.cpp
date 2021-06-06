#include "GameObjects/Goal.hpp"
#include "PongGame.hpp"

Goal::Goal(Team team, float posZ)
	: InvisiblePlane(CG::Vector3(0, 0, posZ), CG::Quaternion::fromLookDirection(CG::Vector3::Down(), CG::Vector3(0, 0, -posZ))),
	m_team(team)
{
}

void Goal::onCollide(CG::GameObject & other)
{
	if (other.hasTag<"ball"_hs>())
		dynamic_cast<PongGame *>(CG::AGame::instance)->onScore(m_team);
}