#pragma once

#include <CG/prefabs/Plane.hpp>
#include <CG/math/Vector3.hpp>

class AnchorSpring : public CG::GameObject
{
public:
	AnchorSpring(const CG::Vector3 &anchor, CG::GameObject &b, double force, double restLength);

private:
	void update(double d) noexcept;
	void lateUpdate(double d) noexcept;

private:
	CG::Vector3 m_anchor;
	CG::GameObject &m_obj;

	double m_force, m_restLength;
};
