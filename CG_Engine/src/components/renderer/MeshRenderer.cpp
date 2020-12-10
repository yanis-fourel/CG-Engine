#include <stdexcept>
#include <fmt/format.h>

#include <assimp/Importer.hpp>        
#include <assimp/scene.h>          
#include <assimp/postprocess.h>    

#include "CG/components/renderer/MeshRenderer.hpp"


CG::MeshRenderer::MeshRenderer(const std::string &path)
{
	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(path, 0);

	if (!scene)
		throw std::runtime_error(fmt::format("Could not import asset '{}' : {}", path, importer.GetErrorString()));

	const auto builder = processAssimpScene(scene);

	m_drawable = builder.build();
}


CG::DrawableBuilder CG::MeshRenderer::processAssimpScene(const aiScene *scene)
{
	DrawableBuilder result;

	for (unsigned i = 0; i < scene->mNumMeshes; ++i) {
		const auto *current = scene->mMeshes[i];

		for (unsigned j = 0; j < current->mNumVertices; ++j) {
			assert(current->mNormals && "Currently needs normals");

			const auto &v = current->mVertices[j];
			const auto &n = current->mNormals[j];

			result.vertices.push_back(CG::Vertex{
				   CG::Vector3(v.x, v.y, v.z),
				   CG::Vector3(n.x, n.y, n.z),
				   CG::Color::White() // TODO: color ?
				});
		}

		for (unsigned j = 0; j < current->mNumFaces; ++j) {
			const auto &v = current->mFaces[j];

			for (unsigned k = 0; k < v.mNumIndices; ++k)
				result.indices.push_back(v.mIndices[k]);
		}
	}

	return result;
}
