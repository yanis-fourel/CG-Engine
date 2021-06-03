#pragma once


#include <CG/math/Vector3.hpp>
#include <CG/math/Quaternion.hpp>

class InvisiblePlane : public CG::GameObject
{
public:
	InvisiblePlane(const CG::Vector3 &pos, const CG::Quaternion &rotation);
};
