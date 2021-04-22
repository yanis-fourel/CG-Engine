#include "CG/prefabs/Sphere.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/renderer/ShapeRenderer.hpp"
#include "CG/components/collider/SphereCollider.hpp"

CG::prefabs::Sphere::Sphere(const Vector3 &pos, float radius)
{
	auto &t = addComponent<CG::Transform>();
	t.position = pos;
	t.scale = Vector3(radius * 2, radius * 2, radius * 2);

	addComponent<CG::ShapeRenderer>(CG::ShapeRenderer::Sphere());
	addComponent<CG::SphereCollider>();
}
