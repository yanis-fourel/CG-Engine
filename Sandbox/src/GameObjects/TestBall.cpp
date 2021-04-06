#include <CG/components/renderer/SphereRenderer.hpp>

#include "GameObjects/TestBall.hpp"

TestBall::TestBall(const CG::Vector3 &pos, float radius, const CG::Material &material) : CG::prefabs::Sphere(pos, radius)
{
	getComponent<CG::SphereRenderer>().setMaterial(material);
	setTag<"simulation_object"_hs>();
}
