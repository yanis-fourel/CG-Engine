#include <CG/components/renderer/MeshRenderer.hpp>
#include <CG/components/Transform.hpp>

#include "GameObjects/Mesh.hpp"
#include "AssetDir.hpp"

Mesh::Mesh(const std::string &path)
{
	addComponent<CG::MeshRenderer>(std::string(ASSET_DIR) + path);

	addComponent<CG::Transform>();
}
