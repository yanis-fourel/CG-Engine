#include "CG/prefabs/Sphere.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/renderer/SphereRenderer.hpp"
#include "CG/components/collider/SphereCollider.hpp"

CG::prefabs::Sphere::Sphere(const Vector3 &pos, float radius)
{
	auto &t = addComponent<CG::Transform>();
	t.position = pos;
	t.scale = Vector3(radius, radius, radius);

	addComponent<CG::SphereRenderer>();
	addComponent<CG::SphereCollider>(&t);
}
