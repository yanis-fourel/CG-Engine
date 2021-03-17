#include "CG/prefabs/Sphere.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/renderer/SphereRenderer.hpp"

CG::prefabs::Sphere::Sphere(const Vector3 &pos, float radius, const Color &color)
{
	auto &t = addComponent<CG::Transform>();
	t.position = pos;
	t.scale = Vector3(radius, radius, radius);

	addComponent<CG::SphereRenderer>(color);
}
