#include "CG/prefabs/PointLight.hpp"

#include "CG/components/PointLight.hpp"
#include "CG/components/Transform.hpp"

CG::prefabs::PointLight::PointLight(const Vector3 &pos, const Color &color)
{
	addComponent<CG::Transform>().position = pos;
	addComponent<CG::PointLight>().color = color;
}
