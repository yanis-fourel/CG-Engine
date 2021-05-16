#pragma once

#include <CG/prefabs/Plane.hpp>
#include <CG/math/Vector3.hpp>

class AnchorCable : public CG::GameObject
{
public:
	AnchorCable(const CG::Vector3 &anchor, CG::GameObject &b, double length);

private:
	void resolve() noexcept;
	void lateUpdate(double d) override;

private:
	CG::Vector3 m_anchor;
	CG::GameObject &m_obj;

	double m_length;
};
