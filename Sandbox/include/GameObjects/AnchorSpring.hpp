#pragma once

#include <CG/prefabs/Plane.hpp>
#include <CG/math/Vector3.hpp>

class AnchorSpring : public CG::AGameObject
{
public:
	AnchorSpring(const CG::Vector3 &anchor, CG::AGameObject &b, double force, double restLength);

private:
	void update(double d) noexcept;

private:
	CG::Vector3 m_anchor;
	CG::AGameObject &m_obj;

	double m_force, m_restLength;
};
