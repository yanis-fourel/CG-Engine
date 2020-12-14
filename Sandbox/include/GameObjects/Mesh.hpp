#pragma once

#include <CG/GameObject.hpp>

class Mesh : public CG::AGameObject
{
public:
	Mesh(const std::string &path, bool relativeToAssetFolder = true);

	auto getPath() const noexcept -> const std::string &;

private:
	std::string m_path;
};
