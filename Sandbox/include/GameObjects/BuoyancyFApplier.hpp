#pragma once

#include <CG/prefabs/Plane.hpp>
#include <CG/math/Vector3.hpp>

// Note: computation is terribly off. Will fix later if needed
class BuoyancyFApplier : public CG::GameObject
{
public:
	BuoyancyFApplier(CG::GameObject &obj, float seaLevel, float seaDensity);

	void setDensity(float val) noexcept { m_density = val; }
private:
	void update(double d) noexcept;

private:
	CG::GameObject &m_obj;

	float m_seaLevel;
	float m_density;
};
