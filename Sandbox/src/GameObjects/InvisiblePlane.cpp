#include <limits>

#include <CG/components/Rigidbody.hpp>
#include <CG/components/collider/PlaneCollider.hpp>
#include <CG/components/renderer/ShapeRenderer.hpp>
#include <CG/components/Transform.hpp>

#include "GameObjects/InvisiblePlane.hpp"


InvisiblePlane::InvisiblePlane(const CG::Vector3 &pos, const CG::Quaternion &rotation)
{
	auto &t = addComponent<CG::Transform>(pos, rotation, CG::Vector3::One() * 9999);

	//addComponent<CG::ShapeRenderer>(CG::ShapeRenderer::Plane()); // Debug

	addComponent<CG::PlaneCollider>();

	auto &rb = addComponent<CG::Rigidbody>();

	rb.setMass(std::numeric_limits<double>::infinity());
}
