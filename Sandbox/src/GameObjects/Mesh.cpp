#include <CG/components/renderer/MeshRenderer.hpp>
#include <CG/components/Transform.hpp>

#include "GameObjects/Mesh.hpp"
#include "AssetDir.hpp"

Mesh::Mesh(const std::string &path, bool relativeToAssetFolder) : m_path(path)
{
	if (relativeToAssetFolder)
		m_path = std::string(ASSET_DIR) + m_path;

	addComponent<CG::MeshRenderer>(m_path);

	addComponent<CG::Transform>();
}

auto Mesh::getPath() const noexcept -> const std::string &
{
	return m_path;
}