#pragma once

#include <CG/prefabs/Plane.hpp>
#include <CG/math/Vector3.hpp>

class Spring : public CG::GameObject
{
public:
	Spring(CG::GameObject &a, CG::GameObject &b, double force, double restLength);

private:
	void update(double d) override;
	void lateUpdate(double d) override;
	
private:
	CG::GameObject &m_obj1;
	CG::GameObject &m_obj2;

	double m_force, m_restLength;
};
