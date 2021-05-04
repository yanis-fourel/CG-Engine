#pragma once

#include <CG/prefabs/Plane.hpp>
#include <CG/math/Vector3.hpp>

class Rod : public CG::GameObject
{
public:
	Rod(CG::GameObject &a, CG::GameObject &b, double length);

private:
	void update(double d) noexcept;

private:
	CG::GameObject &m_obj1;
	CG::GameObject &m_obj2;

	double m_length;
};
