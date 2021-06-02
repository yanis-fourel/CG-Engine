#include "CG/prefabs/Plane.hpp"
#include "CG/components/renderer/ShapeRenderer.hpp"
#include "CG/components/collider/PlaneCollider.hpp"
#include "CG/components/Transform.hpp"

CG::prefabs::Plane::Plane()
{
	addComponent<CG::Transform>();
	addComponent<CG::ShapeRenderer>(CG::ShapeRenderer::Plane());
	addComponent<CG::PlaneCollider>();
}

CG::prefabs::Plane::Plane(const Vector3 &pos, const Quaternion &rotation, const Vector2 &size)
	: Plane()
{
	auto &t = getComponent<CG::Transform>();

	t.position = pos;
	t.rotation = rotation;
	t.scale = Vector3(size.x, 1, size.y);
}
