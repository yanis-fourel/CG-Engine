#include "CG/components/Rigidbody.hpp"

void CG::Rigidbody::addImpulse(const CG::Vector3 &val) noexcept
{
	setVelocity(getVelocity() + val);
}