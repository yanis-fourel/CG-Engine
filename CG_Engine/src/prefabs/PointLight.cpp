#include "CG/prefabs/PointLight.hpp"

#include "CG/components/Transform.hpp"
#include "CG/components/PointLight.hpp"

CG::prefabs::PointLight::PointLight(const Vector3 &pos, const Color &color)
{
	addComponent<Transform>().position = pos;
	addComponent<CG::PointLight>().color = color;
}
