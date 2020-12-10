#pragma once

#include <CG/GameObject.hpp>

class Mesh : public CG::AGameObject
{
public:
	Mesh(const std::string &path);
};
