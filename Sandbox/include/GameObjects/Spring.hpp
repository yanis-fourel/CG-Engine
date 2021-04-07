#pragma once

#include <CG/prefabs/Plane.hpp>
#include <CG/math/Vector3.hpp>
#include <CG/Material.hpp>

class Spring : public CG::AGameObject
{
public:
	Spring(CG::AGameObject &a, CG::AGameObject &b, double force, double restLength);

private:
	void update(double d) noexcept;

private:
	CG::AGameObject &m_obj1;
	CG::AGameObject &m_obj2;

	double m_force, m_restLength;
};
