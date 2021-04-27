#include "CG/prefabs/Plane.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/renderer/ShapeRenderer.hpp"
#include "CG/components/collider/PlaneCollider.hpp"

CG::prefabs::Plane::Plane(const Vector3 &pos, const Quaternion &rotation, const Vector2 &size)
{
	addComponent<CG::Transform>(pos, rotation, Vector3(size.x, 1, size.y));
	addComponent<CG::ShapeRenderer>(CG::ShapeRenderer::Plane());
	addComponent<CG::PlaneCollider>();
}
