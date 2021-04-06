#include "CG/prefabs/Plane.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/renderer/PlaneRenderer.hpp"
#include "CG/components/collider/PlaneCollider.hpp"

CG::prefabs::Plane::Plane(const Vector3 &pos, const Quaternion &normalRotation, const Vector2 &size)
{
	auto &t = addComponent<CG::Transform>(pos, normalRotation, Vector3(size.x, size.y, 1));
	addComponent<CG::PlaneRenderer>();
	addComponent<CG::PlaneCollider>();
}
